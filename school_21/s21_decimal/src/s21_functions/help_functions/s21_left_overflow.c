#include "../../s21_decimal.h"

void s21_left_overflow(decimal_overflow *value) {
  short b[5];
  for (int i = 0; i < 5; i++) b[i] = s21_check_bit_state(value->bits[i], 31);
  for (int i = 0; i < 6; i++) value->bits[i] <<= 1;
  for (int i = 0; i < 5; i++)
    if (b[i]) value->bits[i + 1] = s21_set_bit(value->bits[i + 1], 0);
}