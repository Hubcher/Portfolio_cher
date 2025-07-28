#include "../s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  if (result) {
    decimal_overflow res = {{0, 0, 0, 0, 0, 0}};
    for (int i = 0; i < 96; i++) {
      if (s21_check_bit_state(value_1.bits[i / 32], i % 32)) {
        decimal_overflow tmp = {{0, 0, 0, 0, 0, 0}};
        s21_copy_overflow(&tmp, res);
        s21_overflow_binary_addition(tmp, s21_left_n_times_overflow(value_2, i),
                                     &res);
      }
    }
    unsigned int scale =
        s21_get_exp(value_1.bits[3]) || s21_get_exp(value_2.bits[3])
            ? ((s21_get_exp(value_1.bits[3]) + s21_get_exp(value_2.bits[3]))
               << 16)
            : 0;
    if ((s21_get_sign(value_1.bits[3]) ^ s21_get_sign(value_2.bits[3])))
      scale |= MINUS;

    error = s21_large_number_max(res, scale);
    if (!error) {
      s21_initialize_decimal(result);
      result->bits[3] = scale;
      s21_normalize_to_lower_exp(res, result);
      while (s21_check_divisible_by_10(*result) &&
             s21_get_exp(result->bits[3]) != 0) {
        s21_divide_by_10(result);
        result->bits[3] -= 1 << 16;
      }
      if (s21_check_zero(*result) && s21_get_exp(result->bits[3]) >= 28) {
        error = 1;
        s21_initialize_decimal(result);
      }
    }
  }
  return error;
}
