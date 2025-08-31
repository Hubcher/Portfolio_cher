#include "../s21_matrix.h"

int Comparing_Matrix_Elements(double num1, double num2, long double precision) {
  long double diff = fabs(num1 - num2);
  return (diff <= precision);
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  // 1 SUCCESS
  // 0 FAILURE
  int comparison_status = SUCCESS;
  if (A->columns == B->columns && A->rows == B->rows) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (!Comparing_Matrix_Elements(A->matrix[i][j], B->matrix[i][j],
                                       1e-7)) {
          comparison_status = FAILURE;
          break;
        }
      }
      if (comparison_status == FAILURE) break;
    }
  }
  return comparison_status;
}