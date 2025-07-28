#include "../../s21_decimal.h"

void s21_up_exp(decimal_overflow *v1, int diff1) {
  decimal_overflow ten = {{10, 0, 0, 0, 0, 0}};

  while (diff1) {
    *v1 = multiply_large_numbers(*v1, ten);
    diff1--;
  }
}