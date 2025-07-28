#include "../../s21_decimal.h"

void s21_copy_overflow(decimal_overflow *dest, decimal_overflow src) {
  for (int i = 0; i < 6; i++) {
    dest->bits[i] = src.bits[i];
  }
}