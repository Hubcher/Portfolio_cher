#include "../s21_tests.h"

START_TEST(sub_1) {
  s21_decimal one = {{-676479428, 227282592, -959778769, 786432}};
  s21_decimal two = {{797166276, 1118242106, -1500410035, -2146959360}};
  s21_decimal res = {0};
  int code = s21_sub(one, two, &res);
  ck_assert_int_eq(code, 0);
  s21_decimal res2 = {{-1099129433, 485616151, -1500076516, 524288}};
  ck_assert_int_eq(s21_is_equal(res, res2), 1);
}
END_TEST

START_TEST(sub_2) {
  s21_decimal one = {{1820781911, 1284925087, -63216361, 65536}};
  s21_decimal two = {{-1223975596, -721211597, -1689350057, 65536}};
  s21_decimal res = {0};
  int code = s21_sub(one, two, &res);
  ck_assert_int_eq(code, 0);
  s21_decimal res2 = {{-1250209789, 2006136683, 1626133695, 65536}};
  ck_assert_int_eq(s21_is_equal(res, res2), 1);
}
END_TEST

START_TEST(sub_3) {
  s21_decimal one = {{1483440529, 1571411001, 2036459939, 1441792}};
  s21_decimal two = {{-1357595838, -773041342, -1541731952, 983040}};
  s21_decimal res = {0};
  int code = s21_sub(one, two, &res);
  ck_assert_int_eq(code, 0);
  s21_decimal res2 = {{-1600667513, 747403123, -1541732155, -2146500608}};
  ck_assert_int_eq(s21_is_equal(res, res2), 1);
}
END_TEST

START_TEST(sub_4) {
  s21_decimal one = {{-250033034, -1474578636, 1154699324, -2147352576}};
  s21_decimal two = {{-2038637339, 1231518576, 701746080, -2146369536}};
  s21_decimal res = {0};
  int code = s21_sub(one, two, &res);
  ck_assert_int_eq(code, 0);
  s21_decimal res2 = {{-148950668, -1474581650, 1154699324, -2147352576}};
  ck_assert_int_eq(s21_is_equal(res, res2), 1);
}
END_TEST

START_TEST(sub_5) {
  s21_decimal one = {{-558176365, 451145307, -1035983588, -2146697216}};
  s21_decimal two = {{1201865891, 653769810, 491002713, -2147352576}};
  s21_decimal res = {0};
  int code = s21_sub(one, two, &res);
  ck_assert_int_eq(code, 0);
  s21_decimal res2 = {{-734287703, -745953035, 491002712, 131072}};
  ck_assert_int_eq(s21_is_equal(res, res2), 1);
}
END_TEST

START_TEST(sub_6) {
  s21_decimal one = {{4, 0, 0, 0x80000000}};
  s21_decimal two = {{5, 0, 0, 0}};
  s21_decimal res = {0};
  int code = s21_sub(one, two, &res);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(res.bits[0], 9);
  ck_assert_int_eq(res.bits[3], 0x80000000);
}
END_TEST

Suite *suite_sub(void) {
  Suite *s = suite_create("suite_sub");
  TCase *tc = tcase_create("sub_tc");
  tcase_add_test(tc, sub_1);
  tcase_add_test(tc, sub_2);
  tcase_add_test(tc, sub_3);
  tcase_add_test(tc, sub_4);
  tcase_add_test(tc, sub_5);
  tcase_add_test(tc, sub_6);

  suite_add_tcase(s, tc);
  return s;
}