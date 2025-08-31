#include "../s21_matrix.h"

void s21_create_minor(matrix_t *A, matrix_t *minor, int row_to_skip,
                      int col_to_skip) {
  int n = A->rows - 1;
  s21_create_matrix(n, n, minor);

  for (int i = 0, row = 0; i < A->rows; i++) {
    if (i == row_to_skip) {
      continue;
    }
    for (int j = 0, col = 0; j < A->columns; j++) {
      if (j == col_to_skip) {
        continue;
      }
      minor->matrix[row][col++] = A->matrix[i][j];
    }
    row++;
  }
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int error = 0;
  if (bad_size_matrix(A)) {
    error = 1;
  } else if (A->rows == A->columns) {
    matrix_t minor;
    double det;
    s21_create_matrix(A->columns, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        s21_create_minor(A, &minor, i, j);
        s21_determinant(&minor, &det);
        result->matrix[i][j] = (i + j) % 2 == 0 ? det : -det;
        s21_remove_matrix(&minor);
      }
    }
  } else {
    error = 2;
  }
  return error;
}