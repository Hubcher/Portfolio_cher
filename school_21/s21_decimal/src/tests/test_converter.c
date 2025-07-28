#include "../s21_tests.h"

START_TEST(from_int_to_decimal_1) {
  int src = -280899064;
  s21_decimal res = {0};
  int code = s21_from_int_to_decimal(src, &res);
  ck_assert_int_eq(code, 0);
  s21_decimal res2 = {{280899064, 0, 0, -2147483648}};
  ck_assert_int_eq(s21_is_equal(res, res2), 1);
}
END_TEST

START_TEST(from_int_to_decimal_2) {
  int src = 28089544;
  s21_decimal res = {0};
  int code = s21_from_int_to_decimal(src, &res);
  ck_assert_int_eq(code, 0);
  s21_decimal res2 = {{28089544, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(res, res2), 1);
}
END_TEST

START_TEST(from_decimal_to_int_1) {
  s21_decimal src = {{1413123423, -577635409, 927694699, 0}};
  int res = 0;
  int code = s21_from_decimal_to_int(src, &res);
  ck_assert_int_eq(code, 1);
  int res2 = 0;
  ck_assert_int_eq(res, res2);
}
END_TEST

START_TEST(from_decimal_to_int_2) {
  s21_decimal src = {{1413123423, 0, 0, 0}};
  int res = 0;
  int code = s21_from_decimal_to_int(src, &res);
  ck_assert_int_eq(code, 0);
  int res2 = 1413123423;
  ck_assert_int_eq(res, res2);
}
END_TEST

START_TEST(from_decimal_to_float_1) {
  s21_decimal src = {{12345678, 0, 0, 0x00040000}};
  float res = 0;
  int code = s21_from_decimal_to_float(src, &res);
  ck_assert_int_eq(code, 0);
  float res2 = 1234.5678;
  ck_assert_float_eq(res, res2);
}
END_TEST

START_TEST(from_float_to_decimal_1) {
  float src = -3.0075832E-15;
  s21_decimal res = {0};
  int code = s21_from_float_to_decimal(src, &res);
  ck_assert_int_eq(code, 0);
  s21_decimal res2 = {{3007583, 0, 0, -2146107392}};
  ck_assert_int_eq(s21_is_equal(res, res2), 1);
}
END_TEST

START_TEST(from_float_to_decimal_2) {
  float src = -3.6229336E-24;
  s21_decimal res = {0};
  int code = s21_from_float_to_decimal(src, &res);
  ck_assert_int_eq(code, 0);
  s21_decimal res2 = {{36229, 0, 0, -2145648640}};
  ck_assert_int_eq(s21_is_equal(res, res2), 1);
}
END_TEST

START_TEST(from_float_to_decimal_3) {
  float src = -1.5454542E-38;
  s21_decimal res = {0};
  int code = s21_from_float_to_decimal(src, &res);
  ck_assert_int_eq(code, 1);
  s21_decimal res2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(res, res2), 1);
}
END_TEST

Suite *suite_converter(void) {
  Suite *s = suite_create("suite_converter");
  TCase *tc = tcase_create("converter_tc");
  tcase_add_test(tc, from_int_to_decimal_1);
  tcase_add_test(tc, from_int_to_decimal_2);
  tcase_add_test(tc, from_decimal_to_int_1);
  tcase_add_test(tc, from_decimal_to_int_2);
  tcase_add_test(tc, from_decimal_to_float_1);
  tcase_add_test(tc, from_float_to_decimal_1);
  tcase_add_test(tc, from_float_to_decimal_2);
  tcase_add_test(tc, from_float_to_decimal_3);

  suite_add_tcase(s, tc);
  return s;
}