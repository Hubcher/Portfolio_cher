#include "../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int err = 1;
  if (dst) {
    err = 0;
    long double res = 0;
    int exp = s21_get_exp(src.bits[3]);
    int sign = s21_get_sign(src.bits[3]);

    for (int i = 0; i < 94; i++) {
      if (s21_check_bit_state(src.bits[i / 31], i % 31)) {
        res += powl(2, i);
      }
    }
    for (; exp > 0; exp--) {
      res /= 10.0L;
    }
    *dst = sign ? -res : res;
  }
  return err;
}
