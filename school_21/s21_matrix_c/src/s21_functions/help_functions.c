#include "../s21_matrix.h"

int Same_matrix_sizes(matrix_t *A, matrix_t *B) {
  return (A->columns == B->columns && A->rows == B->rows);
}

int bad_size_matrix(matrix_t *a) { return (a->rows < 1 || a->columns < 1); }