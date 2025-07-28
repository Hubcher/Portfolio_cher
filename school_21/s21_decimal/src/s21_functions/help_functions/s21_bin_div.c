#include "../../s21_decimal.h"

decimal_overflow bin_div(decimal_overflow v1, decimal_overflow v2) {
  decimal_overflow l = {0}, r = v1, mid = {0};

  decimal_overflow tmp = {0};
  decimal_overflow one = {{1, 0, 0, 0, 0, 0}};
  decimal_overflow res = {0};

  while (s21_overflow_is_less_or_equal(l, r)) {
    s21_overflow_binary_subtraction(r, l, &tmp);

    s21_right(&tmp);
    s21_overflow_binary_addition(l, tmp, &mid);
    tmp = multiply_large_numbers(v2, mid);
    if (s21_first_large_number_greater(tmp, v1)) {
      s21_overflow_binary_subtraction(mid, one, &r);
    } else {
      s21_copy_overflow(&res, mid);
      s21_overflow_binary_addition(mid, one, &l);
    }
  }
  return res;
}