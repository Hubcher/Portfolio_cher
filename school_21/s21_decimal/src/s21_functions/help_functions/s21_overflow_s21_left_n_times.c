#include "../../s21_decimal.h"

decimal_overflow overflow_s21_left_n_times(decimal_overflow number, int shift) {
  for (int i = 0; i < shift; i++) s21_left_overflow(&number);
  return number;
}