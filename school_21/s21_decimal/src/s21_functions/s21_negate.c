#include "../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int err = 1;
  if (result) {
    *result = value;
    result->bits[3] ^= 1U << 31;
    err = 0;
  }
  return err;
}