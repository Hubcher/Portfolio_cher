#include "../s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;

  if (result) {
    int sign1 = s21_get_sign(value_1.bits[3]);
    int sign2 = s21_get_sign(value_2.bits[3]);

    decimal_overflow val1 = {
        {value_1.bits[0], value_1.bits[1], value_1.bits[2], 0, 0, 0}};
    decimal_overflow val2 = {
        {value_2.bits[0], value_2.bits[1], value_2.bits[2], 0, 0, 0}};
    decimal_overflow res = {0};

    unsigned int exp =
        s21_compare_and_set_exp(&val1, &val2, value_1.bits[3], value_2.bits[3]);

    value_1.bits[3] = s21_clear_bit(value_1.bits[3], 31);
    value_2.bits[3] = s21_clear_bit(value_2.bits[3], 31);

    if ((sign1 ^ sign2) == 0) {
      s21_overflow_binary_addition(val1, val2, &res);
    } else if (sign1 && !sign2) {
      if (s21_is_less_or_equal(value_1, value_2)) {
        s21_overflow_binary_subtraction(val2, val1, &res);
      } else {
        s21_overflow_binary_subtraction(val1, val2, &res);
        exp |= MINUS;
      }

    } else if (!sign1 && sign2) {
      if (s21_is_greater_or_equal(value_1, value_2)) {
        s21_overflow_binary_subtraction(val1, val2, &res);
      } else {
        s21_overflow_binary_subtraction(val2, val1, &res);
        exp |= MINUS;
      }
    }

    if (sign1 && sign2) exp |= MINUS;

    error = s21_large_number_max(res, exp);
    if (!error) {
      s21_initialize_decimal(result);
      result->bits[3] = exp;
      s21_normalize_to_lower_exp(res, result);
      while (s21_check_divisible_by_10(*result) &&
             s21_get_exp(result->bits[3]) != 0) {
        s21_divide_by_10(result);
        result->bits[3] -= 1 << 16;
      }
    }
  }

  return error;
}