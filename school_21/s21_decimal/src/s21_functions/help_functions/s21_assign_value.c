#include "../../s21_decimal.h"

void s21_assign_value(s21_decimal *target, s21_decimal source) {
  for (int i = 0; i < 4; i++) {
    target->bits[i] = source.bits[i];
  }
}