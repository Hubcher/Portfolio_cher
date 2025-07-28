#include "../../s21_decimal.h"

int s21_divide_by_10(s21_decimal *decimal_num) {
  unsigned int remainder = 0;
  long long int temporary;
  for (int i = 2; i >= 0; --i) {
    temporary = (unsigned)decimal_num->bits[i] + ((long long)(remainder) << 32);
    remainder = temporary % 10;
    decimal_num->bits[i] = temporary / 10;
  }
  return remainder;
}
