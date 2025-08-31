#include "../s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = 0;
  if (bad_size_matrix(A) || bad_size_matrix(B)) {
    error = 1;
  } else if (A->columns == B->rows) {
    int new_rows = A->rows;
    int new_columns = B->columns;
    int k_max = A->columns;
    s21_create_matrix(new_rows, new_columns, result);
    for (int i = 0; i < new_rows; i++) {
      for (int j = 0; j < new_columns; j++) {
        for (int k = 0; k < k_max; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  } else {
    error = 2;
  }
  return error;
}