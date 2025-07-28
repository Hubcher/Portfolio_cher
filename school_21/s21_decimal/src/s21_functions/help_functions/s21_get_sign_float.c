#include "../../s21_decimal.h"

int s21_get_sign_float(double floating_num) {
  union Data float_data;
  float_data.f = floating_num;
  int sign = s21_check_bit_state(float_data.i, 31);
  return sign;
}