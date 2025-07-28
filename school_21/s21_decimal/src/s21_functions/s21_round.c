#include "../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int err = 1;
  if (result) {
    int sign = s21_get_sign(value.bits[3]);
    s21_decimal one = {{1, 0, 0, 0}};
    s21_decimal ten = {{10, 0, 0, 0}};
    s21_decimal tmp;
    s21_decimal mod;
    s21_assign_value(&tmp, value);
    int scaleMask = s21_get_exp(value.bits[3]);
    while (scaleMask > 1) {
      s21_divide_by_10(&tmp);
      scaleMask--;
    }
    if (scaleMask == 1) {
      s21_assign_value(&value, tmp);
      s21_divide_by_10(&tmp);
      s21_multiply_value(tmp, ten, &tmp);
      s21_subtract_binary(value, tmp, &mod);
      s21_divide_by_10(&value);
      if (mod.bits[0] > 4) s21_add_value(value, one, &value);
      scaleMask--;
      s21_set_exp(&(value.bits[3]), scaleMask);
    }
    s21_assign_value(result, value);
    result->bits[3] ^= (-sign ^ result->bits[3]) & (1U << 31);
    err = 0;
  }
  return err;
}
