#include "../s21_tests.h"

START_TEST(equal_1) {
  s21_decimal first = {{1, 0, 0, 0}};
  s21_decimal second = {{1, 0, 0, 0}};
  ck_assert_int_eq(1, s21_is_equal(first, second));
  ck_assert_int_eq(0, s21_is_not_equal(first, second));
  ck_assert_int_eq(0, s21_is_less(first, second));
  ck_assert_int_eq(1, s21_is_less_or_equal(first, second));
  ck_assert_int_eq(0, s21_is_greater(first, second));
  ck_assert_int_eq(1, s21_is_greater_or_equal(first, second));
}
END_TEST

START_TEST(equal_2) {
  s21_decimal first = {{4323131, 423432, 3213414, 0x80000000}};
  s21_decimal second = {{4323131, 423432, 3213414, 0x80000000}};
  ck_assert_int_eq(1, s21_is_equal(first, second));
  ck_assert_int_eq(0, s21_is_not_equal(first, second));
  ck_assert_int_eq(0, s21_is_less(first, second));
  ck_assert_int_eq(1, s21_is_less_or_equal(first, second));
  ck_assert_int_eq(0, s21_is_greater(first, second));
  ck_assert_int_eq(1, s21_is_greater_or_equal(first, second));
}
END_TEST

START_TEST(equal_3) {
  s21_decimal first = {{4323131, 423432, 3213414, 0x80000000}};
  s21_decimal second = {{4323132, 423432, 3213414, 0x80000000}};
  ck_assert_int_eq(0, s21_is_equal(first, second));
  ck_assert_int_eq(1, s21_is_not_equal(first, second));
  ck_assert_int_eq(0, s21_is_less(first, second));
  ck_assert_int_eq(0, s21_is_less_or_equal(first, second));
  ck_assert_int_eq(1, s21_is_greater(first, second));
  ck_assert_int_eq(1, s21_is_greater_or_equal(first, second));
}
END_TEST

START_TEST(equal_4) {
  s21_decimal first = {{4323131, 423432, 3213414, 0x80080000}};
  s21_decimal second = {{4323131, 423432, 3213414, 0x80080000}};
  ck_assert_int_eq(1, s21_is_equal(first, second));
  ck_assert_int_eq(0, s21_is_not_equal(first, second));
  ck_assert_int_eq(0, s21_is_less(first, second));
  ck_assert_int_eq(1, s21_is_less_or_equal(first, second));
  ck_assert_int_eq(0, s21_is_greater(first, second));
  ck_assert_int_eq(1, s21_is_greater_or_equal(first, second));
}
END_TEST

START_TEST(equal_5) {
  s21_decimal first = {{4323131, 423432, 3213414, 0x80080000}};
  s21_decimal second = {{4323131, 423432, 3213414, 0x80090000}};
  ck_assert_int_eq(0, s21_is_equal(first, second));
  ck_assert_int_eq(1, s21_is_not_equal(first, second));
  ck_assert_int_eq(1, s21_is_less(first, second));
  ck_assert_int_eq(1, s21_is_less_or_equal(first, second));
  ck_assert_int_eq(0, s21_is_greater(first, second));
  ck_assert_int_eq(0, s21_is_greater_or_equal(first, second));
}
END_TEST

START_TEST(equal_8) {
  s21_decimal first = {{4323135, 423432, 3213414, 0x00000000}};
  s21_decimal second = {{4323131, 423432, 3213414, 0x00000000}};
  ck_assert_int_eq(0, s21_is_equal(first, second));
  ck_assert_int_eq(1, s21_is_not_equal(first, second));
  ck_assert_int_eq(0, s21_is_less(first, second));
  ck_assert_int_eq(0, s21_is_less_or_equal(first, second));
  ck_assert_int_eq(1, s21_is_greater(first, second));
  ck_assert_int_eq(1, s21_is_greater_or_equal(first, second));
}
END_TEST

START_TEST(equal_6) {
  s21_decimal first = {{1, 1, 1, 0x00000000}};
  s21_decimal second = {{4323131, 423432, 3213414, 0x80000000}};
  ck_assert_int_eq(0, s21_is_equal(first, second));
  ck_assert_int_eq(1, s21_is_not_equal(first, second));
  ck_assert_int_eq(0, s21_is_less(first, second));
  ck_assert_int_eq(0, s21_is_less_or_equal(first, second));
  ck_assert_int_eq(1, s21_is_greater(first, second));
  ck_assert_int_eq(1, s21_is_greater_or_equal(first, second));
}
END_TEST

Suite *suite_is_equal(void) {
  Suite *s = suite_create("suite_equal");
  TCase *tc = tcase_create("equal_tc");
  tcase_add_test(tc, equal_1);
  tcase_add_test(tc, equal_2);
  tcase_add_test(tc, equal_3);
  tcase_add_test(tc, equal_4);
  tcase_add_test(tc, equal_5);
  tcase_add_test(tc, equal_6);
  tcase_add_test(tc, equal_8);

  suite_add_tcase(s, tc);
  return s;
}