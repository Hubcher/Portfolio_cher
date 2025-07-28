#include "../s21_tests.h"

START_TEST(add_1) {
  s21_decimal one = {{525962363, 1170336598, -1105568354, -2147483648}};
  s21_decimal two = {{-1287256572, -1511129146, 1407240824, 786432}};
  s21_decimal res = {0};
  int code = s21_add(one, two, &res);
  ck_assert_int_eq(code, 0);
  s21_decimal res2 = {{-846107589, 1164292544, -1105568354, -2147483648}};
  ck_assert_int_eq(s21_is_equal(res, res2), 1);
}
END_TEST

START_TEST(add_2) {
  s21_decimal one = {{-628228278, -998587337, 1333010306, -2146500608}};
  s21_decimal two = {{278233596, -626950562, -386918083, -2146566144}};
  s21_decimal res = {0};
  int code = s21_add(one, two, &res);
  ck_assert_int_eq(code, 0);
  s21_decimal res2 = {{-1502576150, -2015299485, -253617052, -2146566144}};
  ck_assert_int_eq(s21_is_equal(res, res2), 1);
}
END_TEST

START_TEST(add_3) {
  s21_decimal two = {{-1474260036, 1682539518, -820064485, 786432}};
  s21_decimal one = {{-1471102815, 587280253, 1193335044, -2146828288}};
  s21_decimal res = {0};
  int code = s21_add(one, two, &res);
  ck_assert_int_eq(code, 0);
  s21_decimal res2 = {{-382618391, 98008455, 1158586016, -2146828288}};
  ck_assert_int_eq(s21_is_equal(res, res2), 1);
}
END_TEST

START_TEST(add_4) {
  s21_decimal one = {{-1692774941, -1237887454, -197456237, -2146369536}};
  s21_decimal two = {{-1924376384, 891884082, 317550970, -2147287040}};
  s21_decimal res = {0};
  int code = s21_add(one, two, &res);
  ck_assert_int_eq(code, 0);
  s21_decimal res2 = {{511565478, 330666101, -1119457594, -2147221504}};
  ck_assert_int_eq(s21_is_equal(res, res2), 1);
}
END_TEST

START_TEST(add_5) {
  s21_decimal one = {{0, 0, 0, 1048576}};
  s21_decimal two = {{0, 0, 0, 1835008}};
  s21_decimal res = {0};
  int code = s21_add(one, two, &res);
  ck_assert_int_eq(code, 0);
  s21_decimal res2 = {{0, 0, 0, 1835008}};
  ck_assert_int_eq(s21_is_equal(res, res2), 1);
}
END_TEST

START_TEST(add_6) {
  s21_decimal one = {{-1474260036, 1682539518, -820064485, 786432}};
  s21_decimal two = {{-1471102815, 587280253, 1193335044, -2146828288}};
  s21_decimal res = {0};
  int code = s21_add(one, two, &res);
  ck_assert_int_eq(code, 0);
  s21_decimal res2 = {{-382618391, 98008455, 1158586016, -2146828288}};
  ck_assert_int_eq(s21_is_equal(res, res2), 1);
}
END_TEST

START_TEST(add_7) {
  s21_decimal one = {{419935895, -836885827, -742003637, 327680}};
  s21_decimal two = {{4170291, 883859341, 477076499, -2147221504}};
  s21_decimal res = {0};
  int code = s21_add(one, two, &res);
  ck_assert_int_eq(code, 0);
  s21_decimal res2 = {{-378232985, 1085544644, 1217801332, -2147155968}};
  ck_assert_int_eq(s21_is_equal(res, res2), 1);
}
END_TEST

START_TEST(add_8) {
  s21_decimal one = {{5, 0, 0, 0}};
  s21_decimal two = {{4, 0, 0, 0x80000000}};
  s21_decimal res = {0};
  int code = s21_add(one, two, &res);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(res.bits[0], 1);
}
END_TEST

START_TEST(add_9) {
  s21_decimal one = {{4, 0, 0, 0x80000000}};
  s21_decimal two = {{5, 0, 0, 0}};
  s21_decimal res = {0};
  int code = s21_add(one, two, &res);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(res.bits[0], 1);
}
END_TEST

Suite *suite_add(void) {
  Suite *s = suite_create("suite_add");
  TCase *tc = tcase_create("add_tc");
  tcase_add_test(tc, add_1);
  tcase_add_test(tc, add_2);
  tcase_add_test(tc, add_3);
  tcase_add_test(tc, add_4);
  tcase_add_test(tc, add_5);
  tcase_add_test(tc, add_6);
  tcase_add_test(tc, add_7);
  tcase_add_test(tc, add_8);
  tcase_add_test(tc, add_9);

  suite_add_tcase(s, tc);
  return s;
}