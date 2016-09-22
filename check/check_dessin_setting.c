#include <check.h>
#include "../print/lib/dessin_setting_functions.h"


extern doc_data informations;
extern display windparams;

START_TEST(wrong_conversion){
  char *lon = "12.499";
  char *lat = "18.877";
  char *resx = malloc(10);
  char *resy = malloc(10);

  sprintf(resx,"%f",(conversion(lon,lat)).x);
  sprintf(resy,"%f",(conversion(lon,lat)).y);

  ck_assert_str_eq(resx,resy);
}
END_TEST


START_TEST(wrong_type_conversion){
  char *lon = "12,499";
  char *lat = "18.877";
  char *resx = malloc(10);
  char *resy = malloc(10);

  sprintf(resx,"%f",(conversion(lon,lat)).x);
  sprintf(resy,"%f",(conversion(lon,lat)).y);

  ck_assert_str_eq(resx,"0.000000");
  ck_assert_str_eq(resy,"0.000000");
}
END_TEST


START_TEST(get_coordonnee){
  informations.hashmap = hashmap_new();
  windparams.scale = 2;
  windparams.current_height = 720;
  informations.min_lon = 72.0021115;
  informations.min_lat = 70.0021115;
  char *ref = "124684699";
  data *dat= malloc(sizeof(data));
  dat->longitude = malloc(100);
  dat->longitude = "75.1546545";
  dat->latitude = malloc(100);
  dat->latitude = "79.1546545";
  hashmap_put(informations.hashmap,(char*)ref,(any_t*)&dat);
  point p = recupere_coordonnee(ref);
  char *resx = malloc(100);
  char *resy = malloc(100);

  sprintf(resx,"%f",p.x);
  sprintf(resy,"%f",p.y);
  ck_assert_str_eq(resx,"0.000000");
  ck_assert_str_eq(resy,"0.000000");
}
END_TEST


Suite *parse_suite(void){
  TCase *tc_core, *tc_limits;
  Suite *s;

  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, get_coordonnee); 
  
  tc_limits = tcase_create("Limits");
  tcase_add_test(tc_limits, wrong_conversion);
  tcase_add_test(tc_limits, wrong_type_conversion);
  
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
