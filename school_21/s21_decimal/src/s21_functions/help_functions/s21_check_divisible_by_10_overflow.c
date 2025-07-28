#include "../../s21_decimal.h"

int s21_check_divisible_by_10_overflow(decimal_overflow n) {
  decimal_overflow tmp = {0};
  for (int i = 0; i < 6; ++i) tmp.bits[i] = n.bits[i];
  return !s21_divide_by_10_overflow(&tmp);
}