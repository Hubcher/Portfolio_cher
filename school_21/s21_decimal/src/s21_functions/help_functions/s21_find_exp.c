#include "../../s21_decimal.h"

int s21_find_exp(decimal_overflow res, decimal_overflow my_integer) {
  int scale = 0;
  int down = 28;
  while (!s21_overflow_is_equal(res, my_integer) && down > 0) {
    s21_divide_by_10_overflow(&res);
    scale++;
    down--;
  }
  return scale;
}