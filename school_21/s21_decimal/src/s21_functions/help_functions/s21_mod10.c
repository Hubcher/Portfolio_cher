#include "../../s21_decimal.h"

void s21_mod10(decimal_overflow value, decimal_overflow *mod) {
  decimal_overflow ten = {{10, 0, 0, 0, 0, 0}};
  decimal_overflow tmp = value;
  if (mod) {
    s21_divide_by_10_overflow(&tmp);
    tmp = multiply_large_numbers(tmp, ten);
    s21_overflow_binary_subtraction(value, tmp, mod);
  }
}
