#include "../../s21_decimal.h"

int s21_compare_and_set_exp(decimal_overflow *num_1, decimal_overflow *num_2,
                            unsigned int scale_1, unsigned int scale_2) {
  int flag = 0;
  if (s21_get_exp(scale_1) > s21_get_exp(scale_2)) {
    s21_normalization(num_2, s21_get_exp(scale_1) - s21_get_exp(scale_2));
    flag = scale_2 = scale_1;
  } else if (s21_get_exp(scale_1) < s21_get_exp(scale_2)) {
    s21_normalization(num_1, s21_get_exp(scale_2) - s21_get_exp(scale_1));
    flag = scale_1 = scale_2;
  } else {
    flag = scale_1;
  }
  return flag;
}