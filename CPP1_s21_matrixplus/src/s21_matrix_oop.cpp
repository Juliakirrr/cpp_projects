#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() {  // Default constructor
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

S21Matrix::S21Matrix(int rows, int cols)
    : rows_(rows), cols_(cols) {  // not default constructor
  if (rows_ < 1 || cols_ < 1) {
    throw std::length_error(invalid_matrix);
  } else {
    matrix_ = new double *[rows_];
    for (int i = 0; i < rows; i++) {
      matrix_[i] = new double[cols];
    }
    rows_ = rows;
    cols_ = cols;
    null();
  }
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : S21Matrix(other.rows_, other.cols_) {  // copy constructor
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix &&other) noexcept
    : rows_{other.rows_}, cols_{other.cols_}, matrix_{other.matrix_} {
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

S21Matrix::~S21Matrix() {  // Destructor
  if (matrix_ != nullptr && rows_ > 0 && cols_ > 0) {
    for (int i = 0; i < rows_; ++i) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
}

//

void S21Matrix::CheckMatrix() {
  if (matrix_ == nullptr || rows_ < 1 || cols_ < 1) {
    throw std::length_error(invalid_matrix);
  }
}

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  bool error = 1;
  if (matrix_ == nullptr || other.matrix_ == nullptr || rows_ < 1 ||
      cols_ < 1) {
    throw std::length_error(invalid_matrix);
  }
  if (rows_ == 0 || cols_ == 0 || other.rows_ == 0 || other.cols_ == 0) {
    error = 0;
  } else if ((rows_ != other.rows_) || (cols_ != other.cols_)) {
    error = 0;
  } else if ((rows_ == other.rows_) && (cols_ == other.cols_)) {  // если равны
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < other.cols_; j++) {
        if ((fabs(matrix_[i][j] - other.matrix_[i][j])) >= 0.0000001) {
          error = 0;
        }
      }
    }
  }
  return error;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ == other.rows_ && cols_ == other.cols_) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
      }
    }
  } else {
    throw std::length_error(invalid_matrix);
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ == other.rows_ && cols_ == other.cols_) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
      }
    }
  } else {
    throw std::length_error(invalid_matrix);
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] * num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ == other.rows_) {  // если колонки 1 == рядочкам 2

    S21Matrix result(rows_, other.cols_);

    double abc = 0.0;
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < other.cols_; j++) {
        for (int k = 0; k < cols_; k++) {
          abc = matrix_[i][k] * other.matrix_[k][j];
          result.matrix_[i][j] = result.matrix_[i][j] + abc;
        }
      }
    }

    *this = result;

  } else {
    throw std::length_error(invalid_matrix);
  }
}

S21Matrix S21Matrix::Transpose() {
  CheckMatrix();
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[j][i] = matrix_[i][j];
    }
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  CheckMatrix();
  if (rows_ != cols_) {
    throw std::length_error(invalid_matrix);
  }

  S21Matrix result(rows_, cols_);

  if (rows_ == 1 && cols_ == 1) {
    result.matrix_[0][0] = 1 / matrix_[0][0];
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        result.matrix_[i][j] = take_minor(i, j);
        if (((i + j + 2) % 2) == 1) {
          result.matrix_[i][j] = result.matrix_[i][j] * -1;
        }
      }
    }
  }

  return result;
}

double S21Matrix::take_minor(int ia, int ja) {
  double first = 0;
  if (cols_ == 1) {
    ia = abs(ia - 1);
    ja = abs(ja - 1);
    first = matrix_[ia][ja];
  } else {
    S21Matrix B(rows_ - 1, cols_ - 1);
    int a = 0, b = 0;

    for (int i = 0; i < rows_;
         i++) {  // перезапись в маленьку матрицу из большой
      for (int j = 0; j < cols_; j++) {
        if (i != ia && j != ja) {
          B.matrix_[a][b] = matrix_[i][j];
          b++;
          if (b > rows_ - 2) {
            a++;
            b = 0;
          }
        }
      }
    }

    first = B.Determinant();
  }
  return first;
}

double S21Matrix::Determinant() {
  CheckMatrix();
  if (rows_ != cols_) {
    throw std::length_error(invalid_matrix);
  }
  int sign = 1;
  S21Matrix B(rows_, cols_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < rows_; j++) {
      B.matrix_[i][j] = matrix_[i][j];
    }
  }

  double mul = 0;
  for (int i = 0; i < B.rows_; i++) {
    for (int j = i + 1; j < B.cols_; j++) {
      if (B.matrix_[i][j] != 0 && B.matrix_[i][i] != 0) {  // если там где то 0
        mul = B.matrix_[j][i] / B.matrix_[i][i];

        for (int k = 0; k < B.cols_; k++) {
          B.matrix_[j][k] = B.matrix_[j][k] - (B.matrix_[i][k] * mul);
        }
      } else if (B.matrix_[i][i] == 0 && B.matrix_[j][i] != 0) {
        for (int k = 0; k < B.cols_; k++) {
          double tmp = B.matrix_[i][k];
          B.matrix_[i][k] = B.matrix_[j][k];
          B.matrix_[j][k] = tmp;
        }
        sign = sign * (-1);
      }
    }
  }
  double result = sign;
  for (int i = 0; i < B.cols_; i++) {
    result = result * B.matrix_[i][i];
  }

  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  CheckMatrix();
  if (rows_ != cols_) {
    throw std::length_error(invalid_matrix);
  }
  S21Matrix C;
  double abc = Determinant();
  if (abc == 0) {
    throw std::length_error(calc_error);
  }

  if (rows_ == 1 && cols_ == 1) {
    C = *this;
    C.matrix_[0][0] = 1 / C.matrix_[0][0];
    // std::cout << "wlkclwksmclkwancl\n";
  } else {
    abc = 1 / abc;
    S21Matrix B = CalcComplements();
    C = B.Transpose();
    C.MulNumber(abc);
  }
  return C;
}

void S21Matrix::SetColumns(int cols) {
  if (cols < 1) {
    throw std::length_error(invalid_matrix);
  }
  S21Matrix result(rows_, cols);
  int min_cols = std::min(cols, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < min_cols; j++) {
      result.matrix_[i][j] = matrix_[i][j];
    }
  }

  FreeMatrix();

  matrix_ = result.matrix_;
  rows_ = result.rows_;
  cols_ = result.cols_;

  result.matrix_ = nullptr;
}

void S21Matrix::SetRows(int rows) {
  if (rows < 1) {
    throw std::length_error(invalid_matrix);
  }
  S21Matrix result(rows, cols_);

  int min_rows = std::min(rows, rows_);
  for (int i = 0; i < min_rows; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[i][j] = matrix_[i][j];
    }
  }

  FreeMatrix();

  matrix_ = result.matrix_;
  rows_ = result.rows_;
  cols_ = result.cols_;

  result.matrix_ = nullptr;
}

void S21Matrix::FreeMatrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
  rows_ = 0;
  cols_ = 0;
}

void S21Matrix::output() {
  std::cout << "row " << rows_ << " cols " << cols_ << "\n";

  for (int i = 0; i < rows_; i++) {
    printf("%-2d|", i);
    for (int j = 0; j < cols_; j++) {
      printf("%6.2lf", matrix_[i][j]);
    }
    std::cout << '\n';
  }
  // std::cout << '\n';
  printf("адрес %p\n\n", matrix_);
}

S21Matrix S21Matrix::operator+=(const S21Matrix &other) {
  this->SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  this->SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-=(const S21Matrix &other) {
  this->SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  this->SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(const S21Matrix &other) {
  this->MulMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  this->MulMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(const double num) {
  this->MulNumber(num);
  return *this;
}

S21Matrix S21Matrix::operator*(const double num) {
  this->MulNumber(num);
  return *this;
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  this->FreeMatrix();

  if (other.rows_ < 1 || other.cols_ < 1) {
    throw std::length_error(invalid_matrix);
  }
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = new double *[other.rows_];

  for (int i = 0; i < other.rows_; i++) {
    matrix_[i] = new double[other.cols_];
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
  return *this;
}

bool S21Matrix::operator==(const S21Matrix &other) {
  return this->EqMatrix(other);
}

double &S21Matrix::operator()(int i, int j) {
  if (i > rows_ || j > cols_ || i < 0 || j < 0) {
    throw std::length_error(invalid_matrix);
  }
  return matrix_[i][j];
}

double &S21Matrix::operator()(int i, int j) const {
  if (i > rows_ || j > cols_ || i < 0 || j < 0) {
    throw std::length_error(invalid_matrix);
  }
  return matrix_[i][j];
}

void S21Matrix::null() {
  if (matrix_ != nullptr && cols_ > 0 && rows_ > 0) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = 0;
      }
    }
  }
}