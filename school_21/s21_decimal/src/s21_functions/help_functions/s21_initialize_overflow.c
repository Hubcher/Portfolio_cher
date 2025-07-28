#include "../../s21_decimal.h"

void s21_initialize_overflow(decimal_overflow *ovfl) {
  for (int i = 0; i < 6; i++) {
    ovfl->bits[i] = 0;
  }
}