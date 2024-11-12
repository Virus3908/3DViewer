/// @mainpage
/// @file s21_backend.h
/// @author machelch
/// @brief 3D viewer
/// @version 1.0
/// @date 2024-11-12
///
/// @copyright Copyright (c) 2024

#ifndef S21_BACKEND_H
#define S21_BACKEND_H

#include "matrix/s21_matrix.h"
#include "model/s21_model.h"
#include "transform/s21_transform.h"

namespace s21 {

/// @brief Класс бэкенда
class Backend : public Observable {
 public:
  /// @brief Стандартный конструктор
  Backend();
  /// @brief Стандартный деструктор
  ~Backend() = default;

  /// @brief Очистка матрицы трансформаций
  void clearTransformation();
  /// @brief Чтение новой модели
  /// @param fileName Путь к файлу модели
  /// @return Статус прочтения файла
  Status_e readModel(const std::string &fileName);

  /// @brief Получение ссылки на вектор вершин
  /// @return Ссылка на вектор вершин
  const std::vector<Vertex_t> &getVertices();
  /// @brief Получение ссылки на вектор поверхностей
  /// @return Вектор поверхностей
  const std::vector<Face_t> &getFaces();
  /// @brief Получение ссылки на вектор ребер
  /// @return Вектор ребер
  const std::vector<Edge_t> &getEdges();
  /// @brief Получение ссылки на матрицу трансформаций
  /// @return Матрица трансформаций
  const Matrix &getTransformationMatrix();

  /// @brief Обновление матрицы трансформаций
  /// @param Transformation Тип трансформации
  /// @param isMouse Мышкой произведена трансформация
  /// @param direction Числовое значения применения данной трансформации
  void updateTransformation(TransformationName_e Transformation, bool isMouse,
                            const float &direction);

  /// @brief Обновление стратегии контекста
  /// @param Transformation Тип трансформации
  /// @param directrion Числовое значение прменяемой трансформации
  /// @return Возвращает стратегию новой трансформации
  TransformationStrategy *updateStrategy(TransformationName_e Transformation,
                                         const float &directrion);

 private:
  /// @brief Проверка, не приводит ли трансформация к нулевой матрице
  /// @param mat Матрица трансформаций после применения новой трансформации
  /// @return Возвращает true, когда один из масштбных коэффициентов становится
  /// равен нулю
  bool isZeroTransform(Matrix mat);
  /// @brief Матрица трансформаций
  Matrix TransformationMatrix;
  /// @brief Ссылка на синглтон модели
  Model &model = Model::getModel();
  /// @brief Контекст трансформации
  TransformationContext context;
};
}  // namespace s21

#endif