#include "../s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;

  int sign1 = s21_get_sign(value_1.bits[3]);
  int sign2 = s21_get_sign(value_2.bits[3]);

  decimal_overflow val1 = {
      {value_1.bits[0], value_1.bits[1], value_1.bits[2], 0, 0, 0}};
  decimal_overflow val2 = {
      {value_2.bits[0], value_2.bits[1], value_2.bits[2], 0, 0, 0}};
  decimal_overflow res = {0};

  unsigned int scale =
      s21_compare_and_set_exp(&val1, &val2, value_1.bits[3], value_2.bits[3]);
  value_1.bits[3] = s21_clear_bit(value_1.bits[3], 31);
  value_2.bits[3] = s21_clear_bit(value_2.bits[3], 31);
  scale = s21_clear_bit(scale, 31);

  if (!sign1 && !sign2) {  // два положительных 0 и 0
    if (s21_is_less(value_1, value_2)) {  // value_1 < value_2
      s21_overflow_binary_subtraction(val2, val1, &res);
      scale |= MINUS;
    } else if (!s21_is_equal(value_1,
                             value_2)) {  // не равны, но 1 число больше
      s21_overflow_binary_subtraction(val1, val2, &res);
    }

    // -5 - 2 = -7
  } else if (sign1 && !sign2) {  // 1 - отрицательное, 2 - положительное
    s21_overflow_binary_addition(val1, val2, &res);
    scale |= MINUS;

    // 5 -(-2) = -7
  } else if (!sign1 && sign2) {  // 1 положительное, 2 отрицательное
    s21_overflow_binary_addition(val1, val2, &res);

  } else {
    if (s21_is_greater(value_1, value_2)) {  // value_1 > value_2
      s21_overflow_binary_subtraction(val1, val2, &res);
      scale |= MINUS;
    } else if (!s21_is_equal(value_1, value_2)) {
      s21_overflow_binary_subtraction(val2, val1, &res);
    }
  }

  error = s21_large_number_max(res, scale);
  if (result) {
    if (!error) {
      s21_initialize_decimal(result);
      result->bits[3] = scale;
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