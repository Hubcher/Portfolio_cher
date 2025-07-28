#include "../../s21_decimal.h"

int s21_divide_by_10_overflow(decimal_overflow *n) {
  unsigned int mod = 0;
  long long int tmp;
  for (int i = 5; i >= 0; --i) {
    tmp = (unsigned)n->bits[i] + ((long long)(mod) << 32);
    mod = tmp % 10;
    n->bits[i] = tmp / 10;
  }
  return mod;
}