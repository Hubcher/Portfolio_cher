#include "../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int err = 1;
  if (result) {
    int sign = s21_get_sign(value.bits[3]);
    s21_initialize_decimal(result);
    s21_decimal one = {{1, 0, 0, 0}};
    s21_truncate(value, result);
    if (sign && s21_is_not_equal(value, *result)) {
      s21_add_value(*result, one, result);
    }
    result->bits[3] ^= (-sign ^ result->bits[3]) & (1U << 31);
    err = 0;
  }
  return err;
}