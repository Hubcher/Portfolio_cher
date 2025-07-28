#include "../../s21_decimal.h"

decimal_overflow s21_left_n_times_overflow(s21_decimal number, int shift) {
  decimal_overflow res = {
      {number.bits[0], number.bits[1], number.bits[2], 0, 0, 0}};
  for (int i = 0; i < shift; i++) s21_left_overflow(&res);
  return res;
}