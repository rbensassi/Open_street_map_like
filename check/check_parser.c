/*********************
cc check_parser.c -o check_parser `pkg-config --libs check` `xml2-config --cflags --libs` ../parse/Parse.c ../parse/libs/hashmap_add_functions.c ../parse/libs/hashmap_get_functions.c ../libs/hashmap.c

 ********************/

#include <check.h> 
#include "../parse/libs/Parse.h"

doc_data informations;

START_TEST(test_parse_sax){
  informations.hashmap = hashmap_new();
  informations.hashforeground = hashmap_new();
  informations.hashbackground = hashmap_new();
  informations.nbrelation=-1;
  informations.relation_list= (relation*)(malloc(100*sizeof(relation)));
  
  xmlParserCtxtPtr ctxt;
  xmlSAXHandler sh = { 0 };
  ctxt = xmlCreateFileParserCtxt("../Exemples/01_denver_lafayette.osm");
  sh.startElement = parse_sax;
  ctxt->sax = &sh;
  xmlParseDocument(ctxt);
  ck_assert_int_eq(hashmap_length(informations.hashmap),174);
}
END_TEST


START_TEST(test_parse_sax_not_existing_file){
  informations.hashmap = hashmap_new();
  informations.hashforeground = hashmap_new();
  informations.hashbackground = hashmap_new();
  informations.nbrelation=-1;
  informations.relation_list= (relation*)(malloc(100*sizeof(relation)));
  
  xmlParserCtxtPtr ctxt;
  ctxt = xmlCreateFileParserCtxt("../Exemples/01_denver_lafaette.osm");
  ck_assert_msg(ctxt == NULL, "Erreur lors de la création du contexte");
}
END_TEST


START_TEST(test_parse_sax_not_osm_file){
  informations.hashmap = hashmap_new();
  informations.hashforeground = hashmap_new();
  informations.hashbackground = hashmap_new();
  informations.nbrelation=-1;
  informations.relation_list= (relation*)(malloc(100*sizeof(relation)));
  
  xmlParserCtxtPtr ctxt;
  xmlSAXHandler sh = { 0 };

  ctxt = xmlCreateFileParserCtxt("../Exemples/01_denver_lafayette_not_well.osm");
  ctxt->sax = &sh;
  xmlParseDocument(ctxt);
  
  ck_assert_msg(ctxt->wellFormed == 0, "Document XML mal formé");
}
END_TEST


Suite *parse_suite(void){
  TCase *tc_core, *tc_limits;
  Suite *s;

  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_parse_sax);

  tc_limits = tcase_create("Limits");
  tcase_add_test(tc_limits, test_parse_sax_not_existing_file);
  tcase_add_test(tc_limits, test_parse_sax_not_osm_file);

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
