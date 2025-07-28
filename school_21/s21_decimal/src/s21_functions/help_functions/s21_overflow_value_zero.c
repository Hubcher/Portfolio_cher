#include "../../s21_decimal.h"

int s21_overflow_value_zero(decimal_overflow number) {
  int isZero = 1;
  for (int i = 0; i < 6; i++) {
    if (number.bits[i] != 0) {
      isZero = 0;
    }
  }
  return isZero;
}