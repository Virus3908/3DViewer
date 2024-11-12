#include "s21_matrix.h"

namespace s21 {

Matrix::Matrix() {
  _rows = 0;
  _cols = 0;
  _matrix = nullptr;
}

Matrix::Matrix(int rows, int cols) : _rows(rows), _cols(cols) {
  if (rows <= 0 || cols <= 0) {
    throw std::invalid_argument("Wrong size of matrix");
  }
  createMatrix();
}

Matrix::Matrix(const Matrix& o) : _rows(o._rows), _cols(o._cols) {
  createMatrix();
  for (int i = 0; i < _rows; ++i) {
    for (int j = 0; j < _cols; ++j) {
      _matrix[i][j] = o._matrix[i][j];
    }
  }
}

Matrix::~Matrix() { deleteMatrix(); }

void Matrix::createMatrix() {
  _matrix = new float*[_rows];
  for (int i = 0; i < _rows; ++i) {
    _matrix[i] = new float[_cols]();
  }
}

void Matrix::deleteMatrix() {
  for (int i = 0; i < _rows; ++i) {
    delete[] _matrix[i];
  }
  delete[] _matrix;
}

void Matrix::MulMatrix(const Matrix& o) {
  if (_cols != o._rows) {
    throw std::invalid_argument("Wrong size of matrixes");
  }
  Matrix res(_rows, o._cols);
  for (int i = 0; i < _rows; ++i) {
    for (int j = 0; j < o._cols; ++j) {
      for (int k = 0; k < _cols; ++k) {
        res._matrix[i][j] += (_matrix[i][k] * o._matrix[k][j]);
      }
    }
  }
  *this = res;
}

bool Matrix::operator==(const Matrix& o) const {
  bool res = true;
  if (_rows != o._rows || _cols != o._cols) {
    res = false;
  }
  for (int i = 0; i < _rows && res; ++i) {
    for (int j = 0; j < _cols && res; ++j) {
      if (fabs(_matrix[i][j] - o._matrix[i][j]) > MY_EPS) {
        res = false;
      }
    }
  }
  return res;
}

Matrix& Matrix::operator=(const Matrix& o) {
  deleteMatrix();
  _rows = o._rows;
  _cols = o._cols;
  createMatrix();
  for (int i = 0; i < _rows; ++i) {
    for (int j = 0; j < _cols; ++j) {
      _matrix[i][j] = o._matrix[i][j];
    }
  }
  return *this;
}

Matrix Matrix::operator*(const Matrix& o) {
  Matrix res(*this);
  res.MulMatrix(o);
  return res;
}

float* Matrix::operator[](int row) const {
  if (row >= _rows)
    throw std::out_of_range("Incorrect input, index is out of range");

  return _matrix[row];
}

void Matrix::setIdentity() {
  for (int i = 0; i < _rows; ++i) {
    for (int j = 0; j < _cols; ++j) {
      _matrix[i][j] = i == j ? 1.0 : 0.0;
    }
  }
}

}  // namespace s21