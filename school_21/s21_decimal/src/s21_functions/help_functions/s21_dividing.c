#include "../../s21_decimal.h"

int s21_dividing(s21_decimal val1, s21_decimal val2, decimal_overflow *result) {
  decimal_overflow val_1 = {{val1.bits[0], val1.bits[1], val1.bits[2], 0, 0,
                             0}},
                   val_2 = {{val2.bits[0], val2.bits[1], val2.bits[2], 0, 0,
                             0}},
                   my_integer = {0}, v1cpy = val_1, v2cpy = val_2;
  s21_decimal one = {{1, 0, 0, 0}};
  decimal_overflow big_one = {{1, 0, 0, 0, 0, 0}};
  int ans = s21_get_exp(val1.bits[3]);

  if (!s21_is_equal(val2, one)) {
    int scale1 = s21_get_exp(val1.bits[3]);
    int scale2 = s21_get_exp(val2.bits[3]);
    int up =
        (scale1 != scale2) ? 28 + s21_absolute_value(scale1 - scale2) - 1 : 29;
    s21_compare_exp(&v1cpy, &v2cpy, &val1.bits[3], &val2.bits[3]);
    my_integer = bin_div(v1cpy, v2cpy);
    if (scale1 != scale2) {
      if (s21_is_less(val1, val2) && !s21_is_equal(val2, one)) {
        s21_up_exp(&val_1, up);
      } else if (!s21_is_equal(val2, one))
        s21_up_exp(&val_1, 29);
    } else if (!s21_is_equal(val2, one))
      s21_up_exp(&val_1, 28);
    *result = bin_div(val_1, val_2);
    int scale = s21_find_down(*result, my_integer);
    int down = scale <= 28 ? scale : 28;
    while ((s21_check_overflow(result) && down > 0) ||
           (s21_check_divisible_by_10_overflow(*result) && down > 0)) {
      s21_bank_round(*result, result);
      down--;
    }
    ans = s21_find_exp(*result, my_integer);
  } else {
    *result = bin_div(val_1, big_one);
  }
  return ans;
}