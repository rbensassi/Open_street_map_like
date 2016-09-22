/***
cc check_extension_search.c -o check_hashmap_extension_search `pkg-config --libs check` ../parse/libs/hashmap_add_functions.c ../parse/libs/hashmap_get_functions.c ../print/dessin.c ../Extension/search.c ../libs/hashmap.c ../parse/Parse.c `xml2-config --cflags --libs` `sdl2-config --cflags --libs` -lSDL2_gfx -lm
 ***/

#include <check.h>
#include "../Extension/lib/search.h"

extern display windparams ;
extern doc_data informations;
extern hashmap_map *searchByName;
extern way * waysearched; 
extern char text[30];

START_TEST(search_way){
  informations.hashforeground = hashmap_new();
  searchByName = hashmap_new();
  char *id = malloc(10);
  id = "france";
  char *value = "15825869";
  strcat(text,"france");
  hashmap_put(searchByName,id,(any_t)value);
  way *w=malloc(100);
  w->type = malloc(10);
  w->type = "TEST";
  hashmap_put(informations.hashforeground,"15825869",(any_t)w);
  search();
  ck_assert_ptr_ne(waysearched,NULL);
  ck_assert_str_eq(waysearched->type,"TEST");
}
END_TEST


START_TEST(wrong_search_way){
  informations.hashforeground = hashmap_new();
  searchByName = hashmap_new();
  char *id = malloc(10);
  id = "france";
  char *value = "15825869";
  strcat(text,"argentine");
  hashmap_put(searchByName,id,(any_t)value);
  way *w=malloc(100);
  w->type = malloc(10);
  w->type = "TEST";
  hashmap_put(informations.hashforeground,"15825869",(any_t)w);
  search();
  ck_assert_ptr_eq(waysearched,NULL);
}
END_TEST


Suite *parse_suite(void){
  TCase *tc_core, *tc_limits;
  Suite *s;

  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, search_way);
  
  tc_limits = tcase_create("Limits");
  tcase_add_test(tc_limits, wrong_search_way);

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
