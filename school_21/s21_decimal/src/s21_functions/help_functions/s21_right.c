#include "../../s21_decimal.h"

void s21_right(decimal_overflow *value) {
  short lower_bits[5];
  for (int i = 1; i < 5; i++)
    lower_bits[i] = s21_check_bit_state(value->bits[i], 0);
  for (int i = 0; i < 6; i++) value->bits[i] >>= 1;
  for (int i = 4; i > 0; i--)
    if (lower_bits[i]) value->bits[i - 1] = s21_set_bit(value->bits[i - 1], 31);
}