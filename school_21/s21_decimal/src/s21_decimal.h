#ifndef S21_DECIMAL
#define S21_DECIMAL
#define _GNU_SOURSE_

#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  unsigned int bits[6];
} decimal_overflow;

typedef struct {         // bits[0] младшие 32 бита
  unsigned int bits[4];  // bits[1] средние 32 бита
} s21_decimal;           // bits[2] старшие 32 бита

union Data {
  int i;
  float f;
};

int s21_clear_bit(int num, int idx);

int s21_divide_by_10(s21_decimal *value);
int s21_check_bit_state(int number, int index);
int s21_set_bit(int number, int index);
int s21_invert_bit(int number, int index);
int s21_clear_bit(int number, int index);
void s21_initialize_decimal(s21_decimal *dst);
int s21_absolute_value(int number);
int s21_get_sign(int number);
int s21_get_exp(int number);
int s21_overflow_binary_addition(decimal_overflow value_1,
                                 decimal_overflow value_2,
                                 decimal_overflow *result);
void s21_initialize_overflow(decimal_overflow *dst);
void s21_copy_overflow(decimal_overflow *number1, decimal_overflow number2);
void s21_left_overflow(decimal_overflow *value);
void s21_right(decimal_overflow *value);
decimal_overflow s21_left_n_times_overflow(s21_decimal number, int shift);
decimal_overflow overflow_s21_left_n_times(decimal_overflow number, int shift);
int s21_left(s21_decimal *value);
int s21_left_n_times(s21_decimal *number, int shift);
int s21_check_overflow(decimal_overflow *number);
int s21_compare_and_set_exp(decimal_overflow *num_1, decimal_overflow *num_2,
                            unsigned int scale_1, unsigned int scale_2);
void s21_normalization(decimal_overflow *result, short scale);
void s21_assign_value(s21_decimal *number1, s21_decimal number2);
int s21_check_zero(s21_decimal number);
int s21_add_value(s21_decimal value_1, s21_decimal value_2,
                  s21_decimal *result);
void s21_set_exp(unsigned *scale, unsigned target);
int s21_check_divisible_by_10(s21_decimal n);
int s21_multiply_value(s21_decimal value_1, s21_decimal value_2,
                       s21_decimal *result);
void s21_subtract_binary(s21_decimal value_1, s21_decimal value_2,
                         s21_decimal *result);
int s21_round_off_float(double num);
int s21_get_sign_float(double num);
int s21_get_exp_float(double num);
decimal_overflow multiply_large_numbers(decimal_overflow value_1,
                                        decimal_overflow value_2);
int s21_first_large_number_greater(decimal_overflow number1,
                                   decimal_overflow number2);
decimal_overflow overflow_shift_left_n_times(decimal_overflow number,
                                             int shift);
int s21_overflow_binary_subtraction(decimal_overflow value_1,
                                    decimal_overflow value_2,
                                    decimal_overflow *result);
int s21_large_number_max(decimal_overflow val_1, int scale);
void s21_normalize_to_lower_exp(decimal_overflow value, s21_decimal *result);
int s21_overflow_value_zero(decimal_overflow number);
int s21_divide_by_10_overflow(decimal_overflow *n);
void s21_bank_round(decimal_overflow value, decimal_overflow *result);
void s21_mod10(decimal_overflow value, decimal_overflow *mod);
int s21_dividing(s21_decimal val1, s21_decimal val2, decimal_overflow *result);
int s21_find_exp(decimal_overflow res, decimal_overflow celoe);
int s21_find_down(decimal_overflow res, decimal_overflow celoe);
void s21_up_exp(decimal_overflow *v1, int diff1);
decimal_overflow bin_div(decimal_overflow v1, decimal_overflow v2);
int s21_check_divisible_by_10_overflow(decimal_overflow n);
int s21_overflow_is_equal(decimal_overflow number1, decimal_overflow number2);
int s21_overflow_is_less_or_equal(decimal_overflow number1,
                                  decimal_overflow number2);
void s21_right(decimal_overflow *value);
void s21_compare_exp(decimal_overflow *num_1, decimal_overflow *num_2,
                     unsigned int *scale_1, unsigned int *scale_2);

// Arithmetic Operators
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Comparison Operators
int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);

// Convertors and parsers
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// Another functions
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

/*
Биты от 0 до 15, младшее слово, не используются и должны быть равны нулю.
Биты с 16 по 23 должны содержать показатель степени от 0 до 28, который
указывает степень 10 для разделения целого числа. Биты с 24 по 30 не
используются и должны быть равны нулю. Бит 31 содержит знак; 0 означает
положительный, а 1 означает отрицательный.
*/

#define MINUS 2147483648
#define EXP_INT_MASK 8355840
#define MASK_FLOAT_EXP 1069547520
#define MAX_DEC 4294967295
#define INT_MAX 2147483647

#endif
