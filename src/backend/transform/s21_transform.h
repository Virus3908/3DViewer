/// @mainpage
/// @file s21_transform.h
/// @author machelch
/// @brief 3D viewer
/// @version 1.0
/// @date 2024-11-12
///
/// @copyright Copyright (c) 2024

#ifndef S21_TRANSFORM_H
#define S21_TRANSFORM_H

#include "../matrix/s21_matrix.h"

namespace s21 {

/// @brief Список возможных трансформаций
enum TransformationName_e {
  TranslationX,
  TranslationY,
  TranslationZ,
  Scale,
  RotateX,
  RotateY,
  RotateZ
};

/// @brief Виртуальный класс стратегий
class TransformationStrategy {
 public:
  /// @brief Деструктор стандартный
  virtual ~TransformationStrategy() = default;
  /// @brief Объявление обязательной перегрузки метода
  /// @return Возвращает матрицу применяемых трансформаций
  virtual Matrix applyTransformation() const = 0;
};

/// @brief Класс стратегии перемещения вдоль оси х
class TranslationXStrategy : public TransformationStrategy {
 public:
  /// @brief Конструктор класса
  /// @param x на сколько переместить объект
  TranslationXStrategy(float x);
  /// @brief Объявление обязательной перегрузки метода
  /// @return Возвращает матрицу применяемых трансформаций
  Matrix applyTransformation() const override;

 private:
  /// @brief Перемещение вдоль оси
  float tx;
};

/// @brief Класс стратегии перемещения вдоль оси У
class TranslationYStrategy : public TransformationStrategy {
 public:
  /// @brief Конструктор класса
  /// @param y на сколько переместить объект
  TranslationYStrategy(float y);
  /// @brief Объявление обязательной перегрузки метода
  /// @return Возвращает матрицу применяемых трансформаций
  Matrix applyTransformation() const override;

 private:
  /// @brief Перемещение вдоль оси
  float ty;
};

/// @brief Класс стратегии перемещения вдоль оси Z
class TranslationZStrategy : public TransformationStrategy {
 public:
  /// @brief Конструктор класса
  /// @param z на сколько переместить объект
  TranslationZStrategy(float z);
  /// @brief Объявление обязательной перегрузки метода
  /// @return Возвращает матрицу применяемых трансформаций
  Matrix applyTransformation() const override;

 private:
  /// @brief Перемещение вдоль оси
  float tz;
};

/// @brief Класс стратегии масштабирования
class ScaleStrategy : public TransformationStrategy {
 public:
  /// @brief Конструктор класса
  /// @param s на сколько масштабировать объект
  ScaleStrategy(float s);
  /// @brief Объявление обязательной перегрузки метода
  /// @return Возвращает матрицу применяемых трансформаций
  Matrix applyTransformation() const override;

 private:
  /// @brief Значение масштабирования
  float sAll;
};

/// @brief Класс стратегии вращения вокруг X
class RotateXStrategy : public TransformationStrategy {
 public:
  /// @brief Конструктор класса
  /// @param angle На сколько повернуть объект вокруг оси
  RotateXStrategy(float angle);
  /// @brief Объявление обязательной перегрузки метода
  /// @return Возвращает матрицу применяемых трансформаций
  Matrix applyTransformation() const override;

 private:
  /// @brief Косинус от угла вращения
  float cosA;
  /// @brief Синус от угла вращения
  float sinA;
};

/// @brief Класс стратегии вращения вокруг Y
class RotateYStrategy : public TransformationStrategy {
 public:
  /// @brief Конструктор класса
  /// @param angle На сколько повернуть объект вокруг оси
  RotateYStrategy(float angle);
  /// @brief Объявление обязательной перегрузки метода
  /// @return Возвращает матрицу применяемых трансформаций
  Matrix applyTransformation() const override;

 private:
  /// @brief Косинус от угла вращения
  float cosA;
  /// @brief Синус от угла вращения
  float sinA;
};

/// @brief Класс стратегии вращения вокруг Z
class RotateZStrategy : public TransformationStrategy {
 public:
  /// @brief Конструктор класса
  /// @param angle На сколько повернуть объект вокруг оси
  RotateZStrategy(float angle);
  /// @brief Объявление обязательной перегрузки метода
  /// @return Возвращает матрицу применяемых трансформаций
  Matrix applyTransformation() const override;

 private:
  /// @brief Косинус от угла вращения
  float cosA;
  /// @brief Синус от угла вращения
  float sinA;
};

/// @brief Класс контекста трансформации
class TransformationContext {
 public:
  /// @brief Конструктор контекста
  /// @param initStrategy Указатель на стратегию
  TransformationContext(TransformationStrategy *initStrategy = nullptr);
  /// @brief Деструктор контекста
  ~TransformationContext();
  /// @brief Метод по установке новой стратегии
  /// @param newStrategy Указатель на новую стратегию
  void setStrategy(TransformationStrategy *newStrategy);
  /// @brief Получение матрици трансформаций на основе стратегии
  /// @return Возвращает матрицу трансформаций
  Matrix applyTransformation() const;

 private:
  /// @brief Указатель на стратегию трансформации
  TransformationStrategy *strategy;
};

}  // namespace s21

#endif