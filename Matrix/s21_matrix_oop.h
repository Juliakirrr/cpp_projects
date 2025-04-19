#include <cmath>
#include <iostream>
#include <string>

const std::string invalid_matrix{"Invalid matrix"};
const std::string calc_error{"Calculation error"};

class S21Matrix {
 private:
  // Attributes
  int rows_, cols_;  // Rows and columns
  double **matrix_;  // Pointer to the memory where the matrix is allocated

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other) noexcept;
  ~S21Matrix();

  // ------------------------ default methods -------------------------//
  bool EqMatrix(const S21Matrix &other);
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  //----------------accessor и mutator-----------------------------//

  int getRows() { return rows_; }
  int getCols() { return cols_; }
  double **getMatrix() { return matrix_; }

  void SetRows(int rows);
  void SetColumns(int cols);

  // ------------------------ my methods -------------------------//
  void change();
  void change2();
  void output();
  double take_minor(int ia, int ja);
  void CheckMatrix();
  void FreeMatrix();
  void null();

  //--------------------------- operators-------------------------//

  S21Matrix operator+=(const S21Matrix &other);
  S21Matrix operator+(const S21Matrix &other);
  S21Matrix operator-=(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);
  S21Matrix operator*=(const S21Matrix &other);
  S21Matrix operator*(const S21Matrix &other);
  S21Matrix operator*=(const double num);
  S21Matrix operator*(const double num);
  S21Matrix &operator=(const S21Matrix &other);
  bool operator==(const S21Matrix &other);
  double &operator()(int i, int j);
  double &operator()(int i, int j) const;
};
