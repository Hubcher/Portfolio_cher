#include "../../s21_decimal.h"

void s21_set_exp(unsigned *scale, unsigned target) {
  unsigned sign = s21_get_sign(*scale);
  *scale = target;
  *scale <<= 16;
  if (sign) *scale = s21_set_bit(*scale, 31);
}