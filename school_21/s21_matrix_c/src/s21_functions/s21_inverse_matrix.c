#include "../s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (bad_size_matrix(A) == 1) return 1;
  double det = 0;
  if (A->columns != A->rows) return 2;
  s21_determinant(A, &det);
  if (det == 0) return 2;
  if (A->columns == 1 && A->rows == 1) {
    s21_create_matrix(1, 1, result);
    result->matrix[0][0] = 1. / A->matrix[0][0];
    return 0;
  }
  matrix_t complement, transpose;
  s21_calc_complements(A, &complement);
  s21_transpose(&complement, &transpose);
  s21_mult_number(&transpose, 1. / det, result);
  s21_remove_matrix(&complement);
  s21_remove_matrix(&transpose);
  return 0;
}