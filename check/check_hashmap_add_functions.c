/*********************
cc check_hashmap_add_functions.c -o check_hashmap_add_functions `pkg-config --libs check` ../parse/libs/hashmap_add_functions.c  ../parse/libs/hashmap_get_functions.c ../libs/hashmap.c ../parse/Parse.c `xml2-config --cflags --libs`
 ********************/

#include <check.h> 
#include "../parse/libs/hashmap_add_functions.h"

doc_data informations;
extern int count;
extern int type;
extern way *sway;
extern char *wayid;

START_TEST(adding_node){
  const xmlChar *keyid = (xmlChar *)"id";
  const xmlChar *valueid = (xmlChar *)"124569845";
  const xmlChar *keylat = (xmlChar *)"lat";
  const xmlChar *valuelat = (xmlChar *)"45.2684849";
  const xmlChar *keylon = (xmlChar *)"lon";
  const xmlChar *valuelon = (xmlChar *)"44.2684849";
  const xmlChar **attributs = malloc(100);
  attributs[0] = keyid;
  attributs[1] = valueid;
  attributs[2] = keylat;
  attributs[3] = valuelat;
  attributs[4] = keylon;
  attributs[5] = valuelon;

  informations.hashmap = hashmap_new();
    
  ajoutnode(attributs);
  data *d = malloc(100);
  hashmap_get(informations.hashmap, ((char *)"124569845"),(any_t) &d);
  ck_assert_str_eq(d->latitude,"45.2684849");
  ck_assert_str_eq(d->longitude,"44.2684849");
}
END_TEST


START_TEST(wrong_adding_node){
  const xmlChar *keyid = (xmlChar *)"id";
  const xmlChar *valueid = (xmlChar *)"124569845";
  const xmlChar *keylat = (xmlChar *)"lat";
  const xmlChar *valuelat = (xmlChar *)"45.2684849";
  const xmlChar *keylon = (xmlChar *)"lat";
  const xmlChar *valuelon = (xmlChar *)"44.2684849";
  const xmlChar **attributs = malloc(100);
  attributs[0] = keyid;
  attributs[1] = valueid;
  attributs[2] = keylat;
  attributs[3] = valuelat;
  attributs[4] = keylon;
  attributs[5] = valuelon;

  informations.hashmap = hashmap_new();
  ajoutnode(attributs);
  data *d = malloc(100);
  hashmap_get(informations.hashmap, ((char *)"124569845"),(any_t) &d);
  ck_assert_msg(d == NULL,"Node mal formée");
}
END_TEST


START_TEST(adding_way){
  informations.hashbackground = hashmap_new();
  informations.hashforeground = hashmap_new();

  type = 1;
  count = 0;
  wayid = malloc(sizeof(char*));
  wayid = "789456";
  sway = malloc(sizeof(way));
  sway->type = malloc(100);
  sway->valeur = malloc(100);
  sway->refList = malloc(100*sizeof(char*));
  sway->type = "waterway";
  sway->valeur = "coastline";
  ajoutway(wayid);
  way *d = malloc(100);
  hashmap_get(informations.hashbackground,"789456",(any_t) &d);
  ck_assert_str_eq(d->type,"waterway");
  ck_assert_str_eq(d->valeur,"coastline");

  type = 1;
  count = 0;
  wayid = malloc(sizeof(char*));
  wayid = "789456";
  sway = malloc(sizeof(way));
  sway->type = malloc(100);
  sway->valeur = malloc(100);
  sway->refList = malloc(100*sizeof(char*));
  sway->type = "highway";
  sway->valeur = "primary";
  ajoutway(wayid);
  d = malloc(100);
  hashmap_get(informations.hashforeground,"789456",(any_t) &d);
  ck_assert_str_eq(d->type,"highway");
  ck_assert_str_eq(d->valeur,"primary");

}
END_TEST


START_TEST(wrong_adding_way){
  informations.hashbackground = hashmap_new();
  informations.hashforeground = hashmap_new();
  sway = NULL;
  type = 1;
  count = 0;
  wayid = malloc(sizeof(char*));
  wayid = "789456";
  sway = malloc(sizeof(way));
  sway->type = malloc(100);
  sway->valeur = malloc(100);
  sway->refList = malloc(100*sizeof(char*));
  sway->type = "nothing";
  sway->valeur = "else";
  ajoutway(wayid);
  way *d = malloc(100);
  hashmap_get(informations.hashbackground,"789456",(any_t) &d);
  ck_assert_msg(d==NULL,"Way not found");
}
END_TEST


Suite *parse_suite(void){
  TCase *tc_core, *tc_limits;
  Suite *s;

  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, adding_node);
  tcase_add_test(tc_core, adding_way);
  
  tc_limits = tcase_create("Limits");
  tcase_add_test(tc_limits, wrong_adding_node);
  tcase_add_test(tc_limits, wrong_adding_way);
  
  s = suite_create("SAX");
  suite_add_tcase(s, tc_core);
  suite_add_tcase(s, tc_limits);

  return s;
}

int main(void){
  int failures;
  Suite *s;
  SRunner *sr;

  s = parse_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);
  failures = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (failures == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
  
}
