#include "../../s21_decimal.h"

int s21_large_number_max(decimal_overflow val_1, int scale) {
  decimal_overflow max = {{MAX_DEC, MAX_DEC, MAX_DEC, 0, 0, 0}};
  int err = 0;
  for (int i = 0; i < s21_get_exp(scale); i++) {
    s21_divide_by_10_overflow(&val_1);
  }
  if (s21_first_large_number_greater(val_1, max)) {
    err = s21_get_sign(scale) ? 2 : 1;
  }
  return err;
}