#include "../../s21_decimal.h"

void s21_compare_exp(decimal_overflow *num_1, decimal_overflow *num_2,
                     unsigned int *scale_1, unsigned int *scale_2) {
  if (s21_get_exp(*scale_1) > s21_get_exp(*scale_2)) {
    s21_normalization(num_2, s21_get_exp(*scale_1) - s21_get_exp(*scale_2));
    *scale_2 = *scale_1;
  } else if (s21_get_exp(*scale_1) < s21_get_exp(*scale_2)) {
    s21_normalization(num_1, s21_get_exp(*scale_2) - s21_get_exp(*scale_1));
    *scale_1 = *scale_2;
  }
}