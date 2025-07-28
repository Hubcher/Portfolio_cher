#include "../../s21_decimal.h"

int s21_check_zero(s21_decimal num) {
  for (int i = 0; i < 3; i++) {
    if (num.bits[i] != 0) {
      return 0;
    }
  }
  return 1;
}