#include "../s21_tests.h"

START_TEST(div_1) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(3, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(div_2) {
  s21_decimal val1 = {{100, 0, 0, 0}};
  s21_decimal val2 = {{5, 0, 0, 0}};
  s21_decimal res = {{0}};
  s21_decimal res2 = {{20, 0, 0, 0}};
  s21_div(val1, val2, &res);
  ck_assert_int_eq(1, s21_is_equal(res2, res));
}
END_TEST

START_TEST(div_3) {
  s21_decimal src1, src2, result, origin;
  src1.bits[0] = 0b00000000000000000000000001101000;
  src1.bits[1] = 0b00000000000000000000000000000111;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  origin.bits[0] = 0b01010101010101010101010101111000;
  origin.bits[1] = 0b00000000000000000000000000000010;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  int check = s21_div(src1, src2, &result);
  int check_origin = 0;
  ck_assert_int_eq(check, check_origin);
  ck_assert_int_eq(result.bits[3], origin.bits[3]);
  ck_assert_int_eq(result.bits[2], origin.bits[2]);
  ck_assert_int_eq(result.bits[1], origin.bits[1]);
  ck_assert_int_eq(result.bits[0], origin.bits[0]);
}
END_TEST

START_TEST(div_4) {
  s21_decimal one = {{0, 0, 0, 1048576}};
  s21_decimal two = {{4, 0, 0, 1835008}};
  s21_decimal res = {0};
  int code = s21_div(one, two, &res);
  ck_assert_int_eq(code, 0);
  s21_decimal res2 = {{0, 0, 0, 1835008}};
  ck_assert_int_eq(s21_is_equal(res, res2), 1);
}
END_TEST

START_TEST(div_5) {
  s21_decimal one = {{0, 0, 0, 1835008}};
  s21_decimal two = {{4, 0, 0, 1048576}};
  s21_decimal res = {0};
  int code = s21_div(one, two, &res);
  ck_assert_int_eq(code, 0);
  s21_decimal res2 = {{0, 0, 0, 1835008}};
  ck_assert_int_eq(s21_is_equal(res, res2), 1);
}
END_TEST

START_TEST(div_6) {
  s21_decimal one = {{8888888, 32, 0, 1835008}};
  s21_decimal two = {{8888888, 32, 0, 1835008}};
  s21_decimal res = {0};
  int code = s21_div(one, two, &res);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(1, res.bits[0]);
}
END_TEST

START_TEST(div_7) {
  s21_decimal one = {{8888888, 31231, 31234, 1835008}};
  s21_decimal two = {{8888888, 0, 0, 1835008}};
  s21_decimal res = {0};
  int code = s21_div(one, two, &res);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(2358406166, res.bits[0]);
}
END_TEST

Suite *suite_div(void) {
  Suite *s = suite_create("suite_div");
  TCase *tc = tcase_create("div_tc");
  tcase_add_test(tc, div_1);
  tcase_add_test(tc, div_2);
  tcase_add_test(tc, div_3);
  tcase_add_test(tc, div_4);
  tcase_add_test(tc, div_5);
  tcase_add_test(tc, div_6);
  tcase_add_test(tc, div_7);

  suite_add_tcase(s, tc);
  return s;
}