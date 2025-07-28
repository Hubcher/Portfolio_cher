#include "../../s21_decimal.h"

int s21_check_divisible_by_10(s21_decimal n) {
  s21_decimal temp_num = {0};
  for (int i = 0; i < 3; ++i) temp_num.bits[i] = n.bits[i];
  return !s21_divide_by_10(&temp_num);
}