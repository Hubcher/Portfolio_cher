#include "../s21_tests.h"

START_TEST(round_1) {
  s21_decimal src = {{-1431436709, 1903696154, 897175084, 131072}};
  s21_decimal res = {0};
  int code = s21_round(src, &res);
  ck_assert_int_eq(code, 0);
  s21_decimal res2 = {{801729419, -668157806, 8971750, 0}};
  ck_assert_int_eq(s21_is_equal(res, res2), 1);
}
END_TEST

Suite *suite_round(void) {
  Suite *s = suite_create("suite_round");
  TCase *tc = tcase_create("round_tc");
  tcase_add_test(tc, round_1);

  suite_add_tcase(s, tc);
  return s;
}