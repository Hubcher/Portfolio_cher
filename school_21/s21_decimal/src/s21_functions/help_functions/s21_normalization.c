#include "../../s21_decimal.h"

void s21_normalization(decimal_overflow *result, short scale) {
  decimal_overflow ten = {{10, 0, 0, 0, 0, 0}};
  for (int i = 0; i < scale; i++) {
    *result = multiply_large_numbers(*result, ten);
  }
}