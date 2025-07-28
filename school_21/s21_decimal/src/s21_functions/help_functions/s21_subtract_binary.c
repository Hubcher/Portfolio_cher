#include "../../s21_decimal.h"

void s21_subtract_binary(s21_decimal value_1, s21_decimal value_2,
                         s21_decimal *result) {
  for (int i = 0; i < 96; i++)
    value_2.bits[i / 32] = s21_invert_bit(value_2.bits[i / 32], i);
  value_2.bits[0]++;
  s21_add_value(value_1, value_2, result);
}