/***
cc check_extension_stylefile.c -o check_extension_stylefile `pkg-config --libs check` ../parse/libs/hashmap_add_functions.c ../parse/libs/hashmap_get_functions.c ../print/dessin.c ../Extension/search.c ../Extension/stylefile.c ../libs/hashmap.c ../parse/Parse.c `xml2-config --cflags --libs` `sdl2-config --cflags --libs` -lSDL2_gfx -lm
***/

#include <check.h>
#include "../Extension/lib/stylefile.h"

extern char *xmlcolorfile;

START_TEST(parse_stylefile){
  xmlcolorfile = malloc(100);
  xmlcolorfile = "../Exemples/colorExample01.xml";
  ck_assert_int_eq(parsecolorfile(),1);
}
END_TEST


START_TEST(parse_stylefile_not_good_format1){
  xmlcolorfile = malloc(100);
  xmlcolorfile = "../Exemples/colorExample02.xml";
  parsecolorfile(); //type de way non prise en compte
}
END_TEST


START_TEST(parse_stylefile_not_good_format2){
  xmlcolorfile = malloc(100);
  xmlcolorfile = "../Exemples/colorExample03.xml";
  parsecolorfile(); //format tag non reconnu
}
END_TEST


START_TEST(parse_stylefile_not_existing){
  xmlcolorfile = malloc(100);
  xmlcolorfile = "../Exemples/colorExample11.xml";
  ck_assert_int_eq(parsecolorfile(),-1);
}
END_TEST


Suite *parse_suite(void){
  TCase *tc_core, *tc_limits;
  Suite *s;

  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, parse_stylefile);

  tc_limits = tcase_create("Limits");
  tcase_add_test(tc_limits, parse_stylefile_not_existing);
  tcase_add_exit_test(tc_limits,parse_stylefile_not_good_format1,-1);
  tcase_add_exit_test(tc_limits,parse_stylefile_not_good_format2,-1);
  
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
