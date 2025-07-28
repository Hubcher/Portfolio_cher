#include "../../s21_decimal.h"

int s21_get_exp(int num) {
  unsigned int result = num & EXP_INT_MASK;
  result = result >> 16;
  return result;
}