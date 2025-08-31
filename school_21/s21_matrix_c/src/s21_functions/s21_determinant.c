#include "../s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int error = 0;
  if (A->columns < 1 || A->rows < 1) {
    error = 1;
  } else if (A->columns == A->rows) {
    if (A->columns == 1)
      *result = A->matrix[0][0];
    else if (A->columns == 2) {
      *result =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[1][0] * A->matrix[0][1];
    } else {
      double det = 0;
      matrix_t minor;
      for (int j = 0; j < A->rows; j++) {
        s21_create_minor(A, &minor, 0, j);
        double minor_det;
        s21_determinant(&minor, &minor_det);
        det += (j % 2 == 0 ? 1 : -1) * A->matrix[0][j] * minor_det;
        s21_remove_matrix(&minor);
      }
      *result = det;
    }
  } else {
    error = 2;
  }
  return error;
}