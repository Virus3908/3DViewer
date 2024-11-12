/// @mainpage
/// @file s21_controller.h
/// @author machelch
/// @brief 3D viewer
/// @version 1.0
/// @date 2024-11-12
///
/// @copyright Copyright (c) 2024

#ifndef S21_CONTROLLER_H
#define S21_CONTROLLER_H

#include "../backend/s21_backend.h"

namespace s21 {

/// @brief Класс контроллера
class Controller : public Observer {
 public:
  /// @brief Конструктор контроллера
  explicit Controller();
  /// @brief Деструктор контроллера
  ~Controller();

  /// @brief Загрузка модели
  /// @param fileName Путь до модели
  /// @return Статус прочтения файла
  Status_e loadModel(const std::string &fileName);

  /// @brief Применение трансформации
  /// @param Transformation Тип трансформации
  /// @param isMouse Мышкой произведена трансформация
  /// @param direction Числовое значения применения данной трансформации
  void applyTransformation(TransformationName_e transformation, bool isMouse,
                           float direction);

  /// @brief Перегрузка удаления наблюдателя
  void onObservableDestruction() override;
  /// @brief Обновление от наблюдателей
  void update() override;

  /// @brief Очистка трансформации
  void clearTransformation();

  /// @brief Получение вершин
  /// @return Ссылка на вектор вершин
  const std::vector<Vertex_t> &getVertices() const;
  /// @brief Получение поверхностей
  /// @return Ссылка на вектор поверхностей
  const std::vector<Face_t> &getFaces() const;
  /// @brief Получение ребер
  /// @return Ссылка на вектор ребер
  const std::vector<Edge_t> &getEdges() const;

  /// @brief Получение трансформаций
  /// @return Матрица трансформаций
  Matrix getTransformation() const;

 private:
  /// @brief Указатель на бэк
  Backend *backend_;
  /// @brief Матрица трансформаций
  Matrix transformation;
  /// @brief Имя нынешнего файла
  std::string currentFileName;
};

}  // namespace s21

#endif