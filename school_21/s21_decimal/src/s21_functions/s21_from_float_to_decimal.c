#include "../s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int err = 1;
  int scale = 0;
  double srcd = (double)src;
  int sign = s21_get_sign_float(srcd);
  if (dst && isfinite(srcd)) {
    err = 0;
    s21_initialize_decimal(dst);
    int exp = s21_get_exp_float(srcd);
    if (exp <= 95) {
      if (srcd != 0) {
        while (!truncf(srcd)) {
          srcd *= 10;
          scale += 1;
        }
        if (scale <= 28) {
          while (!truncf(srcd / 1000000) && scale < 28) {
            srcd *= 10;
            scale += 1;
          }
          srcd = fabs(srcd);
          srcd = s21_round_off_float(srcd);
          dst->bits[0] = srcd;
          while (s21_check_divisible_by_10(*dst)) {
            s21_divide_by_10(dst);
            scale--;
          }
          dst->bits[3] = scale << 16;
          dst->bits[3] = sign ? s21_set_bit(dst->bits[3], 31)
                              : s21_clear_bit(dst->bits[3], 31);
        } else {
          err = 1;
        }
      }
    } else {
      err = 1;
    }
  }

  return err;
}