/*********************
cc check_hashmap_get_functions.c -o check_hashmap_get_functions `pkg-config --libs check` `xml2-config --cflags --libs` ../parse/libs/hashmap_get_functions.c
 ********************/

#include <check.h> 
#include "../parse/libs/hashmap_get_functions.h"

const xmlChar **attributs;

START_TEST(get_latitude){
  attributs = malloc(100);
  attributs[0] = (xmlChar *)"id";
  attributs[1] = (xmlChar *)"1254879525";
  attributs[2] = (xmlChar *)"lat";
  attributs[3] = (xmlChar *)"75.2356456";
  
  ck_assert_str_eq(getLatitude(attributs),"75.2356456");
}
END_TEST


START_TEST(wrong_get_latitude){
  attributs = malloc(100);
  attributs[0] = (xmlChar *)"id";
  attributs[1] = (xmlChar *)"1254879525";
  attributs[2] = (xmlChar *)"lon";
  attributs[3] = (xmlChar *)"75.2356456";
  
  ck_assert_str_eq(getLatitude(attributs),NODE_WITHOUT_LATITUDE);
}
END_TEST


START_TEST(get_longitude){
  attributs = malloc(100);
  attributs[0] = (xmlChar *)"id";
  attributs[1] = (xmlChar *)"1254879525";
  attributs[2] = (xmlChar *)"lon";
  attributs[3] = (xmlChar *)"71.2356456";
  
  ck_assert_str_eq(getLongitude(attributs),"71.2356456");
}
END_TEST


START_TEST(wrong_get_longitude){
  attributs = malloc(100);
  attributs[0] = (xmlChar *)"id";
  attributs[1] = (xmlChar *)"1254879525";
  attributs[2] = (xmlChar *)"lat";
  attributs[3] = (xmlChar *)"71.2356456";
  
  ck_assert_str_eq(getLongitude(attributs),NODE_WITHOUT_LONGITUDE);
}
END_TEST


START_TEST(get_bounds){
  attributs = malloc(100);
  attributs[0] = (xmlChar *)"minlat";
  attributs[1] = (xmlChar *)"12.4879525";
  attributs[2] = (xmlChar *)"minlon";
  attributs[3] = (xmlChar *)"71.2356456";
  attributs[4] = (xmlChar *)"maxlat";
  attributs[5] = (xmlChar *)"15.4879525";
  attributs[6] = (xmlChar *)"maxlon";
  attributs[7] = (xmlChar *)"75.2356456";
  
  ck_assert_str_eq(getBounds("maxlon",attributs),"75.2356456");
}
END_TEST


START_TEST(wrong_get_bounds){
  attributs = malloc(100);
  attributs[0] = (xmlChar *)"minlat";
  attributs[1] = (xmlChar *)"12.4879525";
  attributs[2] = (xmlChar *)"minlon";
  attributs[3] = (xmlChar *)"71.2356456";
  attributs[4] = (xmlChar *)"maxlat";
  attributs[5] = (xmlChar *)"15.4879525";
  attributs[6] = (xmlChar *)"maxlon";
  attributs[7] = (xmlChar *)"75.2356456";
  
  ck_assert_str_eq(getBounds("maxlongitude",attributs),BOUND_NOT_FOUND);
}
END_TEST


START_TEST(good_test_type){
  char *type = "waterway";
  
  ck_assert_int_eq(test_type(type),1);
}
END_TEST


START_TEST(wrong_test_type){
  char *type = "yolotype";
  
  ck_assert_int_eq(test_type(type),0);
}
END_TEST


Suite *parse_suite(void){
  TCase *tc_core, *tc_limits;
  Suite *s;

  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, get_latitude);
  tcase_add_test(tc_core, get_longitude);
  tcase_add_test(tc_core, get_bounds);
  tcase_add_test(tc_core, good_test_type);
  
  tc_limits = tcase_create("Limits");
  tcase_add_test(tc_limits, wrong_test_type);
  tcase_add_test(tc_limits, wrong_get_bounds);
  tcase_add_test(tc_limits, wrong_get_latitude);
  tcase_add_test(tc_limits, wrong_get_longitude);
  
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
