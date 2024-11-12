/// @mainpage
/// @file s21_matrix.h
/// @author machelch
/// @brief 3D viewer
/// @version 1.0
/// @date 2024-11-12
///
/// @copyright Copyright (c) 2024

#ifndef __Matrix_H__
#define __Matrix_H__

#include "../../common/s21_common.h"

namespace s21 {

/// @brief Класс матриц
class Matrix {
 public:
  /// @brief Стандартный конструктор
  Matrix();
  /// @brief Конструктор по числу строк и столбцов
  /// @param rows Количество строк
  /// @param cols Количество столбцов
  Matrix(int rows, int cols);
  /// @brief Конструктор копирования
  /// @param o Ссылка на другой объект
  Matrix(const Matrix& o);
  /// @brief Стандартный деструктор для матриц
  ~Matrix();

  /// @brief Оператор сравнения
  /// @param o Ссылка на другой объект для сравнения
  /// @return true или false в зависимости от результата
  bool operator==(const Matrix& o) const;
  /// @brief Оператор копирования
  /// @param o Ссылка на другой объект
  /// @return Возвращает ссылку на копию объекта
  Matrix& operator=(const Matrix& o);
  /// @brief Оператор умножения матриц
  /// @param o Ссылка на другой объект
  /// @return Возвращает матрицу результата
  Matrix operator*(const Matrix& o);
  /// @brief Оператор []
  /// @param row Строка к которой необходим доступ
  /// @return Указатель на начало строки матрицы
  float* operator[](int row) const;

  /// @brief Перемножение матриц
  /// @param o Ссылка на другой объект
  void MulMatrix(const Matrix& o);
  /// @brief Делает матрицу единичной
  void setIdentity();

 private:
  /// @brief Создает матрицу
  void createMatrix();
  /// @brief Удаляет матрицу
  void deleteMatrix();

  /// @brief Кол-во строк
  int _rows;
  /// @brief Кол-во столбцов
  int _cols;
  /// @brief Указатель начало матрицы
  float** _matrix;
};

}  // namespace s21

#endif