#include "../s21_tests.h"

START_TEST(negate_1) {
  s21_decimal src = {{1276213354, 252096555, -1859626015, -2145779712}};
  s21_decimal res = {0};
  int code = s21_negate(src, &res);
  ck_assert_int_eq(code, 0);
  s21_decimal res2 = {{1276213354, 252096555, -1859626015, 1703936}};
  ck_assert_int_eq(s21_is_equal(res, res2), 1);
}
END_TEST

Suite *suite_negate(void) {
  Suite *s = suite_create("suite_megate");
  TCase *tc = tcase_create("negate_tc");
  tcase_add_test(tc, negate_1);

  suite_add_tcase(s, tc);
  return s;
}