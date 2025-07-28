#include "../s21_tests.h"

START_TEST(floor_1) {
  s21_decimal src = {{-365028155, -388739486, -193495542, -2146631680}};
  s21_decimal res = {0};
  int code = s21_floor(src, &res);
  ck_assert_int_eq(code, 0);
  s21_decimal res2 = {{-1265811049, 1761568, 0, -2147483648}};
  ck_assert_int_eq(s21_is_equal(res, res2), 1);
}
END_TEST

Suite *suite_floor(void) {
  Suite *s = suite_create("suite_floor");
  TCase *tc = tcase_create("floor_tc");
  tcase_add_test(tc, floor_1);

  suite_add_tcase(s, tc);
  return s;
}