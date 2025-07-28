#include "../../s21_decimal.h"

int s21_check_bit_state(int num, int idx) { return (num & (1 << idx)) != 0; }