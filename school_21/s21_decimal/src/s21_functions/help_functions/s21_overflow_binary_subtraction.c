#include "../../s21_decimal.h"

int s21_overflow_binary_subtraction(decimal_overflow value_1,
                                    decimal_overflow value_2,
                                    decimal_overflow *result) {
  int err;
  if (!s21_overflow_value_zero(value_2)) {
    for (int i = 0; i < 192; i++)
      value_2.bits[i / 32] = s21_invert_bit(value_2.bits[i / 32], i);
    value_2.bits[0]++;
  }
  err = s21_overflow_binary_addition(value_1, value_2, result);
  return err;
}