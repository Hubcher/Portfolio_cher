#include "../../s21_decimal.h"

int s21_get_exp_float(double floating_num) {
  union Data float_data;
  float_data.f = floating_num;
  int exponent = (float_data.i & MASK_FLOAT_EXP) >> 23;
  exponent = exponent - 127;

  return exponent;
}