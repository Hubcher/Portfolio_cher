#include "../s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int err = s21_check_zero(value_2) ? 3 : 0;
  if (err == 0 && result) {
    int sign = s21_check_bit_state(value_1.bits[3], 31) ^
               s21_check_bit_state(value_2.bits[3], 31);
    decimal_overflow res = {0};
    unsigned int scale = s21_dividing(value_1, value_2, &res);
    if (s21_check_overflow(&res)) err = sign ? 2 : 1;
    if (err == 0) {
      for (int i = 0; i < 3; i++) {
        result->bits[i] = res.bits[i];
      }
      result->bits[3] = (scale << 16) | (sign << 31);
    }
  }
  return err;
}