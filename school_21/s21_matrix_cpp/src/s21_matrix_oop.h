#ifndef S21_MATRIX_OOP_H_
#define S21_MATRIX_OOP_H_

#define EPSILON 1e-7

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <utility>

class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_;

 public:
  int GetRows() { return rows_; };
  int GetCols() { return cols_; };
  void SetRows(int rows_);
  void SetCols(int cols_);

  // Constructors
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix();

  // Matrix Operations
  // noexcept - функция не должна выбрасывать исключения
  bool EqMatrix(const S21Matrix& other) noexcept;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num) noexcept;
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose() noexcept;
  S21Matrix CalcComplements();
  double CalcMinor(int row_to_skip, int col_to_skip);
  double Determinant();
  S21Matrix InverseMatrix();
  S21Matrix GetSubmatrix(int row, int col);

  // Operators
  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(double num);

  bool operator==(const S21Matrix& other) noexcept;
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(double num);

  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other) noexcept;

  // Операторы для обращения к элементам матрицы
  double operator()(int i, int j) const;
  double& operator()(int i, int j);
};

#endif