#include "../../s21_decimal.h"

int s21_invert_bit(int num, int idx) { return (num ^ (1 << idx)); }