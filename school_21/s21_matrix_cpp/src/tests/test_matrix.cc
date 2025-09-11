#include "test_matrix.h"

void print_matrix(S21Matrix& matrix) {
  std::cout << "\nSTART\n";
  for (size_t i = 0; i < (size_t)matrix.GetRows(); ++i) {
    for (size_t j = 0; j < (size_t)matrix.GetCols(); ++j) {
      std::cout << matrix(i, j) << ' ';
    }
    std::cout << '\n';
  }
  std::cout << "\nEND\n" << std::endl;
}

TEST(constructor, basic) {
  S21Matrix matrix1;
  EXPECT_EQ(matrix1.GetCols(), 0);
  EXPECT_EQ(matrix1.GetRows(), 0);
}

TEST(constructor, two_args) {
  S21Matrix matrix1(2, 3);
  EXPECT_EQ(matrix1.GetCols(), 3);
  EXPECT_EQ(matrix1.GetRows(), 2);
}

TEST(constructor, copy) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;

  S21Matrix matrix2(matrix1);

  EXPECT_TRUE(matrix1 == matrix2);
}

TEST(constructor, move) {
  S21Matrix matrix1(4, 3);
  S21Matrix matrix2(4, 3);

  S21Matrix moved(std::move(matrix1));

  EXPECT_TRUE(moved == matrix2);
}

TEST(allocate_memory, negative_values) {
  EXPECT_THROW(S21Matrix(-1, 3), std::invalid_argument);
  EXPECT_THROW(S21Matrix(4, -2), std::invalid_argument);
  EXPECT_THROW(S21Matrix(-5, -5), std::invalid_argument);
}

TEST(SetRows_suite, mutator) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(4, 3);

  matrix1(0, 0) = 1.1;
  matrix1(0, 1) = 1.2;
  matrix1(0, 2) = 1.3;
  matrix1(1, 0) = 1.4;
  matrix1(1, 1) = 1.5;
  matrix1(1, 2) = 1.6;
  matrix1(2, 0) = 1.7;
  matrix1(2, 1) = 1.8;
  matrix1(2, 2) = 1.9;

  matrix2(0, 0) = 1.1;
  matrix2(0, 1) = 1.2;
  matrix2(0, 2) = 1.3;
  matrix2(1, 0) = 1.4;
  matrix2(1, 1) = 1.5;
  matrix2(1, 2) = 1.6;
  matrix2(2, 0) = 1.7;
  matrix2(2, 1) = 1.8;
  matrix2(2, 2) = 1.9;

  matrix2(3, 0) = 2.1;
  matrix2(3, 1) = 2.2;
  matrix2(3, 2) = 2.3;

  matrix2.SetRows(3);

  EXPECT_TRUE(matrix1 == matrix2);
}

TEST(SetRows_suite, accessor_mutator) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(2, 3);

  matrix1(0, 0) = 1.1;
  matrix1(0, 1) = 1.2;
  matrix1(0, 2) = 1.3;
  matrix1(1, 0) = 1.4;
  matrix1(1, 1) = 1.5;
  matrix1(1, 2) = 1.6;
  matrix1(2, 0) = 1.7;
  matrix1(2, 1) = 1.8;
  matrix1(2, 2) = 1.9;

  matrix2(0, 0) = 1.1;
  matrix2(0, 1) = 1.2;
  matrix2(0, 2) = 1.3;
  matrix2(1, 0) = 1.4;
  matrix2(1, 1) = 1.5;
  matrix2(1, 2) = 1.6;

  for (size_t i = 0; i < (size_t)matrix1.GetCols(); ++i) {
    matrix1(2, i) = 0.0;
  }

  matrix2.SetRows(3);
  EXPECT_TRUE(matrix1 == matrix2);
}

TEST(SetCols_suite, mutator) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 4);

  matrix1(0, 0) = 1.1;
  matrix1(0, 1) = 1.2;
  matrix1(0, 2) = 1.3;
  matrix1(1, 0) = 1.4;
  matrix1(1, 1) = 1.5;
  matrix1(1, 2) = 1.6;
  matrix1(2, 0) = 1.7;
  matrix1(2, 1) = 1.8;
  matrix1(2, 2) = 1.9;

  matrix2(0, 0) = 1.1;
  matrix2(0, 1) = 1.2;
  matrix2(0, 2) = 1.3;
  matrix2(0, 3) = 1.3;
  matrix2(1, 0) = 1.4;
  matrix2(1, 1) = 1.5;
  matrix2(1, 2) = 1.6;
  matrix2(1, 3) = 1.6;
  matrix2(2, 0) = 1.7;
  matrix2(2, 1) = 1.8;
  matrix2(2, 2) = 1.9;
  matrix2(2, 3) = 1.9;

  matrix2.SetCols(3);

  EXPECT_TRUE(matrix1 == matrix2);
}

TEST(eq_suite, basic) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 3);

  matrix1(0, 0) = 5;
  matrix1(0, 1) = 1.2;
  matrix1(0, 2) = 1.3;
  matrix1(1, 0) = 1.4;
  matrix1(1, 1) = 1.5;
  matrix1(1, 2) = 1.6;
  matrix1(2, 0) = 1.7;
  matrix1(2, 1) = 1.8;
  matrix1(2, 2) = 1.9;

  matrix2(0, 0) = 5;
  matrix2(0, 1) = 1.2;
  matrix2(0, 2) = 1.3;
  matrix2(1, 0) = 1.4;
  matrix2(1, 1) = 1.5;
  matrix2(1, 2) = 1.6;
  matrix2(2, 0) = 1.7;
  matrix2(2, 1) = 1.8;
  matrix2(2, 2) = 1.9;

  EXPECT_TRUE(matrix1 == matrix2);
}

TEST(eq_suite, not_eq_1) {
  S21Matrix matrix1(3, 2);
  S21Matrix matrix2(3, 3);

  matrix1(0, 0) = 1.1;
  matrix1(0, 1) = 1.2;
  matrix1(1, 0) = 1.4;
  matrix1(1, 1) = 1.5;
  matrix1(2, 0) = 1.7;
  matrix1(2, 1) = 1.8;

  matrix2(0, 0) = 1.1;
  matrix2(0, 1) = 1.2;
  matrix2(0, 2) = 1.3;
  matrix2(1, 0) = 1.4;
  matrix2(1, 1) = 1.5;
  matrix2(1, 2) = 1.6;
  matrix2(2, 0) = 1.7;
  matrix2(2, 1) = 1.8;
  matrix2(2, 2) = 1.9;

  EXPECT_FALSE(matrix1 == matrix2);
}

TEST(sum_suite, basic) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.1;
  matrix1(0, 1) = 2.2;
  matrix1(1, 0) = 3.3;
  matrix1(1, 1) = 4.4;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 5.5;
  matrix2(0, 1) = 6.6;
  matrix2(1, 0) = 7.7;
  matrix2(1, 1) = 8.8;

  matrix1.SumMatrix(matrix2);


  EXPECT_EQ(matrix1(0, 0), 6.6);
  EXPECT_EQ(matrix1(0, 1), 8.8);
  EXPECT_EQ(matrix1(1, 0), 11.0);
  EXPECT_FLOAT_EQ(matrix1(1, 1), 13.2);
}

TEST(sub_suite, basic) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 10.0;
  matrix1(0, 1) = 10.0;
  matrix1(1, 0) = 10.0;
  matrix1(1, 1) = 10.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 5.0;
  matrix2(1, 0) = 5.0;
  matrix2(1, 1) = 5.0;

  matrix1.SubMatrix(matrix2);

  EXPECT_EQ(matrix1(0, 0), 5.0);
  EXPECT_EQ(matrix1(0, 1), 5.0);
  EXPECT_EQ(matrix1(1, 0), 5.0);
  EXPECT_EQ(matrix1(1, 1), 5.0);
}

TEST(mul_number_suite, basic) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 10.0;
  matrix1(0, 1) = 100.0;
  matrix1(1, 0) = 1000.0;
  matrix1(1, 1) = 10000.0;

  double num = 2.5;
  matrix1.MulNumber(num);

  EXPECT_EQ(matrix1(0, 0), 25.0);
  EXPECT_EQ(matrix1(0, 1), 250.0);
  EXPECT_EQ(matrix1(1, 0), 2500.0);
  EXPECT_EQ(matrix1(1, 1), 25000.0);
}

TEST(mul_matrix_suite, basa) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 4.0;
  matrix1(1, 1) = 5.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 7.0;
  matrix2(0, 1) = 8.0;
  matrix2(1, 0) = 9.0;
  matrix2(1, 1) = 10.0;

  matrix1.MulMatrix(matrix2);

  EXPECT_EQ(matrix1(0, 0), 25.0);
  EXPECT_EQ(matrix1(0, 1), 28.0);
  EXPECT_EQ(matrix1(1, 0), 73.0);
  EXPECT_EQ(matrix1(1, 1), 82.0);
}

TEST(transpose_suite, basic) {
  S21Matrix matrix1(2, 3);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(0, 2) = 3.0;
  matrix1(1, 0) = 4.0;
  matrix1(1, 1) = 5.0;
  matrix1(1, 2) = 6.0;

  S21Matrix result = matrix1.Transpose();

  EXPECT_EQ(result(0, 0), 1.0);
  EXPECT_EQ(result(0, 1), 4.0);
  EXPECT_EQ(result(1, 0), 2.0);
  EXPECT_EQ(result(1, 1), 5.0);
  EXPECT_EQ(result(2, 0), 3.0);
  EXPECT_EQ(result(2, 1), 6.0);
}

TEST(calc_complements_suite, basic) {
  S21Matrix matrix1(3, 3);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(0, 2) = 3.0;
  matrix1(1, 0) = 4.0;
  matrix1(1, 1) = 5.0;
  matrix1(1, 2) = 6.0;
  matrix1(2, 0) = 7.0;
  matrix1(2, 1) = 8.0;
  matrix1(2, 2) = 9.0;

  S21Matrix result = matrix1.CalcComplements();

  EXPECT_EQ(result(0, 0), -3.0);
  EXPECT_EQ(result(0, 1), 6.0);
  EXPECT_EQ(result(0, 2), -3.0);
  EXPECT_EQ(result(1, 0), 6.0);
  EXPECT_EQ(result(1, 1), -12.0);
  EXPECT_EQ(result(1, 2), 6.0);
  EXPECT_EQ(result(2, 0), -3.0);
  EXPECT_EQ(result(2, 1), 6.0);
  EXPECT_EQ(result(2, 2), -3.0);
}

TEST(inverse_matrix_suite, basic) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 7.5;
  matrix1(0, 1) = 6.3;
  matrix1(1, 0) = 5.1;
  matrix1(1, 1) = 2.7;

  S21Matrix result = matrix1.InverseMatrix();

  EXPECT_FLOAT_EQ(result(0, 0), -0.22727273);
  EXPECT_FLOAT_EQ(result(0, 1), 0.530303);
  EXPECT_FLOAT_EQ(result(1, 0), 0.429293);
  EXPECT_FLOAT_EQ(result(1, 1), -0.631313);
}

TEST(overloads, multiply) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 6.0;
  matrix2(0, 1) = 7.0;
  matrix2(1, 0) = 8.0;
  matrix2(1, 1) = 9.0;

  S21Matrix matrix3(2, 2);
  matrix3(0, 0) = 22.0;
  matrix3(0, 1) = 25.0;
  matrix3(1, 0) = 50.0;
  matrix3(1, 1) = 57.0;

  S21Matrix result = matrix1 * matrix2;
  EXPECT_TRUE(result == matrix3);
}

TEST(overloads, multiply_scalar_basic) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 2.0;
  matrix2(0, 1) = 4.0;
  matrix2(1, 0) = 6.0;
  matrix2(1, 1) = 8.0;

  S21Matrix result = matrix1 * 2.0;
  EXPECT_TRUE(result == matrix2);
}

TEST(matrix_access_operator_suite, valid_indices) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 1.0;
  matrix(1, 1) = 2.0;
  matrix(2, 2) = 3.0;

  EXPECT_NO_THROW({
    double value = matrix(0, 0);
    EXPECT_EQ(value, 1.0);
  });

  EXPECT_NO_THROW({
    double value = matrix(1, 1);
    EXPECT_EQ(value, 2.0);
  });

  EXPECT_NO_THROW({
    double value = matrix(2, 2);
    EXPECT_EQ(value, 3.0);
  });
}

TEST(matrix_access_operator_suite, const_operator) {
  const S21Matrix matrix(3, 3);
  EXPECT_THROW(matrix(-1, 3), std::invalid_argument);
  EXPECT_THROW(matrix(3, -1), std::invalid_argument);
}

TEST(OperatorSum, 3) {
  S21Matrix a{2, 3};
  S21Matrix b{3, 2};
  EXPECT_ANY_THROW(a + b);
}

TEST(OperatorSub, 3) {
  S21Matrix a{2, 3};
  S21Matrix b{3, 2};
  EXPECT_ANY_THROW(a - b);
}

TEST(OperatorSubAssigment, 3) {
  S21Matrix a{2, 3};
  S21Matrix b{3, 2};
  EXPECT_ANY_THROW(a -= b);
}

TEST(OperatorMulEqMatrix, 4) {
  S21Matrix a{2, 2};
  S21Matrix b{3, 2};
  EXPECT_ANY_THROW(a *= b);
}

TEST(OperatorAssigment, 4) {
  S21Matrix a{30, 30};
  S21Matrix b;
  b = a;
  EXPECT_TRUE(a == b);
}

TEST(SetRows_suite, negative_value) {
  S21Matrix matrix(3, 3);
  EXPECT_THROW(matrix.SetRows(-1), std::invalid_argument);
}

TEST(SetCols_suite, negative_value) {
  S21Matrix matrix(3, 3);
  EXPECT_THROW(matrix.SetCols(-1), std::invalid_argument);
}

TEST(SumMatrix_suite, dimension_mismatch) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(3, 2);
  EXPECT_THROW(matrix1.SumMatrix(matrix2), std::invalid_argument);
}

TEST(SubMatrix_suite, dimension_mismatch) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(3, 2);
  EXPECT_THROW(matrix1.SubMatrix(matrix2), std::invalid_argument);
}

// TEST(MulMatrix_suite, dimension_mismatch) {
//     S21Matrix matrix1(2, 3);
//     S21Matrix matrix2(3, 2);
//     EXPECT_THROW(matrix1.MulMatrix(matrix2), std::invalid_argument);
// }

TEST(InverseMatrix_suite, non_square_matrix) {
  S21Matrix matrix(2, 3);
  EXPECT_THROW(matrix.InverseMatrix(), std::invalid_argument);
}

TEST(Transpose_suite, basic) {
  S21Matrix matrix1(2, 3);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(0, 2) = 3.0;
  matrix1(1, 0) = 4.0;
  matrix1(1, 1) = 5.0;
  matrix1(1, 2) = 6.0;

  S21Matrix result = matrix1.Transpose();

  EXPECT_EQ(result.GetRows(), 3);
  EXPECT_EQ(result.GetCols(), 2);
}

TEST(OperatorSum, dimension_mismatch) {
  S21Matrix a(2, 3);
  S21Matrix b(3, 2);
  EXPECT_ANY_THROW(a + b);
}

TEST(OperatorSub, dimension_mismatch) {
  S21Matrix a(2, 3);
  S21Matrix b(3, 2);
  EXPECT_ANY_THROW(a - b);
}

TEST(OperatorSubAssigment, dimension_mismatch) {
  S21Matrix a(2, 3);
  S21Matrix b(3, 2);
  EXPECT_ANY_THROW(a -= b);
}

TEST(OperatorMulEqMatrix, dimension_mismatch) {
  S21Matrix a(2, 2);
  S21Matrix b(3, 2);
  EXPECT_ANY_THROW(a *= b);
}

TEST(OperatorAssigment, basic) {
  S21Matrix a(30, 30);
  S21Matrix b;
  b = a;
  EXPECT_TRUE(a == b);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}