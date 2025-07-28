#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int err = 1;
  if (dst) {
    s21_initialize_decimal(dst);
    err = 0;
    if (src < 0) dst->bits[3] = MINUS;
    dst->bits[0] = s21_absolute_value(src);
  }
  return err;
}