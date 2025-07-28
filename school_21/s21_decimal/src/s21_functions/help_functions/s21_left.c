#include "../../s21_decimal.h"

int s21_left(s21_decimal *value) {
  short upper_bits[3] = {0};
  int result_status = 0;
  for (int i = 0; i < 3; i++)
    upper_bits[i] = s21_check_bit_state(value->bits[i], 31);
  if (upper_bits[2] == 0) {
    for (int i = 0; i < 3; i++) value->bits[i] <<= 1;
    for (int i = 0; i < 2; i++)
      if (upper_bits[i])
        value->bits[i + 1] = s21_set_bit(value->bits[i + 1], 0);
  } else
    result_status = 1;
  return result_status;
}