#include "../../s21_decimal.h"

int s21_check_overflow(decimal_overflow *number) {
  return (number->bits[3] || number->bits[4] || number->bits[5]);
}