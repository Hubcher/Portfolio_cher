#include "../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int error = 1;
  if (result) {
    int sign = s21_get_sign(value.bits[3]);
    int exp = s21_get_exp(value.bits[3]);
    for (; exp > 0; exp--) {
      s21_divide_by_10(&value);
    }
    s21_set_exp(&value.bits[3], exp);
    s21_assign_value(result, value);
    result->bits[3] ^= (-sign ^ result->bits[3]) & (1U << 31);
    error = 0;
  }
  return error;
}
