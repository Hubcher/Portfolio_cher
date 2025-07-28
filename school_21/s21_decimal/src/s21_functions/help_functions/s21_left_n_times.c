#include "../../s21_decimal.h"

int s21_left_n_times(s21_decimal *value, int times) {
  int result_status = 0;
  for (int i = 0; i < times && !result_status; i++)
    result_status = s21_left(value);
  return result_status;
}