#include "s21_matrix_oop.h"

void S21Matrix::SetRows(int rows) {
  if (rows_ < 1) {
    throw std::invalid_argument(
        "ERROR: INVALID DATA || ROWS MUST BE GREATER THAN ZERO");
  }

  S21Matrix temp_matrix(rows, this->cols_);

  int min_rows = std::min(this->rows_, rows);
  for (int i = 0; i < min_rows; i++) {
    for (int j = 0; j < this->cols_; j++) {
      temp_matrix.matrix_[i][j] = this->matrix_[i][j];
    }
  }

  *this = std::move(temp_matrix);
}

void S21Matrix::SetCols(int cols) {
  if (cols < 1) {
    throw std::invalid_argument(
        "ERROR: INVALID DATA || COLS MUST BE GREATER THAN ZERO");
  }
  S21Matrix temp_matrix(this->rows_, cols);

  int min_cols = std::min(this->cols_, cols);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < min_cols; j++) {
      temp_matrix.matrix_[i][j] = this->matrix_[i][j];
    }
  }
  *this = std::move(temp_matrix);
}

S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

S21Matrix::S21Matrix(int rows, int cols)
    : rows_(rows), cols_(cols), matrix_(nullptr) {
  if (rows < 1 || cols < 1) {
    throw std::invalid_argument(
        "ERROR: INVALID DATA || ROWS AND COLS MUST BE GREATER THAN ZERO");
  }
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols]();
  }
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  matrix_ = new double*[other.rows_];
  for (int i = 0; i < other.rows_; i++) {
    matrix_[i] = new double[other.cols_];
  }

  for (int i = 0; i < other.rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept : S21Matrix() {
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
  std::swap(matrix_, other.matrix_);
}

S21Matrix::~S21Matrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
}

bool S21Matrix::EqMatrix(const S21Matrix& other) noexcept {
  if (other.rows_ != this->rows_ || other.cols_ != this->cols_) {
    return false;
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (std::abs(other(i, j) - matrix_[i][j]) > EPSILON) {
        return false;
      }
    }
  }
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument(
        "ERROR: INVALID DATA || MATRICES MUST BE OF SAME SIZE");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other(i, j);
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument(
        "ERROR: INVALID DATA || MATRICES MUST BE OF SAME SIZE");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < rows_; j++) {
      matrix_[i][j] -= other(i, j);
    }
  }
}

void S21Matrix::MulNumber(const double num) noexcept {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (this->cols_ != other.rows_) {
    throw std::invalid_argument(
        "ERROR: INVALID OPERATION || COLS OF FIRST MATRIX MUST MATCH ROWS OF "
        "SECOND");
  }
  S21Matrix result(this->rows_, other.cols_);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < this->cols_; k++) {
        result(i, j) += this->matrix_[i][k] * other(k, j);
      }
    }
  }
  *this = std::move(result);
}

S21Matrix S21Matrix::Transpose() noexcept {
  S21Matrix result(cols_, rows_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result(j, i) = matrix_[i][j];
    }
  }

  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::invalid_argument(
        "ERROR: INVALID OPERATION || MATRIX MUST BE SQUARE");
  }
  S21Matrix result(rows_, cols_);
  if (rows_ == 1) {
    result.matrix_[0][0] = 1;
    return result;
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      result.matrix_[i][j] = pow(-1, i + j) * CalcMinor(i, j);
    }
  }

  return result;
}

double S21Matrix::CalcMinor(int row_to_skip, int col_to_skip) {
  int n = rows_ - 1;

  S21Matrix minor(n, n);
  for (int i = 0, new_row = 0; i < rows_; i++) {
    if (i == row_to_skip) {
      continue;
    }
    for (int j = 0, new_col = 0; j < cols_; j++) {
      if (j == col_to_skip) {
        continue;
      }
      minor.matrix_[new_row][new_col] = matrix_[i][j];
      ++new_col;
    }
    ++new_row;
  }
  return minor.Determinant();
}

S21Matrix S21Matrix::InverseMatrix() {
  double determinant = this->Determinant();
  if (fabs(determinant) < EPSILON) {
    throw std::invalid_argument("ERROR: INVALID DATA || DETERMINANT IS ZERO");
  }
  S21Matrix matrix_first = this->CalcComplements();
  S21Matrix matrix_second = matrix_first.Transpose();
  matrix_second.MulNumber(1.0 / determinant);

  return matrix_second;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::invalid_argument(
        "ERROR: INVALID OPERATION || MATRIX NUST BE SQUARE");
  }

  if (rows_ == 1) {
    return matrix_[0][0];
  }

  double determinant = 0;
  for (int col = 0; col < cols_; col++) {
    double multiplier = matrix_[0][col];
    S21Matrix submatrix = GetSubmatrix(0, col);
    double sub_det = submatrix.Determinant();
    determinant += (((0 + col) % 2 == 0) ? 1 : -1) * multiplier * sub_det;
  }
  return determinant;
}

S21Matrix S21Matrix::GetSubmatrix(int row, int col) {
  S21Matrix submatrix(rows_ - 1, cols_ - 1);
  int row_shift = 0, col_shift = 0;
  for (int i = 0; i < rows_; i++) {
    if (i == row) {
      row_shift++;
      continue;
    }
    col_shift = 0;
    for (int j = 0; j < cols_; j++) {
      if (j == col) {
        col_shift++;
        continue;
      }
      submatrix.matrix_[i - row_shift][j - col_shift] = matrix_[i][j];
    }
  }
  return submatrix;
}

// operator overloading
S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(double num) {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  this->SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  this->SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  this->MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(double num) {
  this->MulNumber(num);
  return *this;
}

bool S21Matrix::operator==(const S21Matrix& other) noexcept {
  return this->EqMatrix(other);
}

double& S21Matrix::operator()(int i, int j) {
  if (i >= rows_ || j >= cols_ || i < 0 || j < 0) {
    throw std::invalid_argument(
        "ERROR: INDEX OUT OF RANGE || INVALID OPERATION");
  }
  return matrix_[i][j];
}

double S21Matrix::operator()(int i, int j) const {
  if (i >= rows_ || j >= cols_ || i < 0 || j < 0) {
    throw std::invalid_argument(
        "ERROR: INDEX OUT OF RANGE || INVALID OPERATION");
  }
  return matrix_[i][j];
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (&other != this) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
      S21Matrix tmp(other.rows_, other.cols_);
      rows_ = other.rows_;
      cols_ = other.cols_;

      if (matrix_ != nullptr) {
        for (int i = 0; i < rows_; i++) {
          delete[] matrix_[i];
        }
        delete[] matrix_;
      }

      matrix_ = new double*[other.rows_];
      for (int i = 0; i < other.rows_; i++) {
        matrix_[i] = new double[other.cols_];
      }
    }

    for (int i = 0; i < other.rows_; i++) {
      for (int j = 0; j < other.cols_; j++) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }

  return *this;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) noexcept {
  if (&other != this) {
    std::swap(rows_, other.rows_);
    std::swap(cols_, other.cols_);
    std::swap(matrix_, other.matrix_);
  }
  return *this;
}