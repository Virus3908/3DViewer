/// @mainpage
/// @file s21_model.h
/// @author machelch
/// @brief 3D viewer
/// @version 1.0
/// @date 2024-11-12
///
/// @copyright Copyright (c) 2024

#ifndef S21_MODEL_H
#define S21_MODEL_H

#include "../../common/s21_common.h"

namespace s21 {

/// @brief Класс синглтона модели
class Model {
 public:
  /// @brief Доступ к синглтону модели
  /// @return Возвращает ссылку на синглтон
  static Model &getModel();
  /// @brief Очищает модель
  void clearModel();

  /// @brief Считывание файла
  /// @param FileName Путь до файла
  /// @return Взвращает статус выполнения чтения файла
  Status_e readFile(const std::string &FileName);

  /// @brief Получение вектора точек
  /// @return Возвращает ссылку на вектор точек модели
  const std::vector<Vertex_t> &getVertex();
  /// @brief Получение вектора поверхностей
  /// @return Возвращает ссылку на вектор поверхностей
  const std::vector<Face_t> &getFace();
  /// @brief Получение вектора ребер
  /// @return Возвращает ссылку на вектор ребер
  const std::vector<Edge_t> &getEdge();

 protected:
  /// @brief Стандартный конструктор, к нему нет доступа
  Model() = default;
  /// @brief Деструктор, к нему нет доступа
  ~Model() = default;

  /// @brief Удаление конструктора копирования
  /// @param  Нет параметров
  Model(const Model &) = delete;
  /// @brief Удаление конструктора перемещений
  /// @param  Нет параметров
  Model(Model &&) = delete;
  /// @brief Удаление оператора копирования
  /// @param  Нет параметров
  /// @return Нет возвращения
  Model &operator=(const Model &) = delete;

  /// @brief Чтение строки из файла
  /// @param line Строка файла
  /// @return Статус прочтения строки
  Status_e readLine(std::string line);
  /// @brief Чтение строки с точкой и отправление в вектор вершин
  /// @param iss Откуда читать
  /// @return Статус прочтения точки
  Status_e pushVertex(std::istringstream &iss);
  /// @brief Чтение строки с номерами вершин для поверзности и отправление в
  /// вектор поверхностей
  /// @param iss Откуда читать
  /// @return Статус прочтения поверхности
  Status_e pushFace(std::istringstream &iss);
  /// @brief Преобразует поверхность в набор ребер
  /// @param face Ссылка на поверхность
  void getEdgeFromFace(const Face_t &face);

 private:
  /// @brief Вектор вершин
  std::vector<Vertex_t> vertices;
  /// @brief Вектор поверхностей
  std::vector<Face_t> faces;
  /// @brief Вектор ребер
  std::vector<Edge_t> edges;
};

}  // namespace s21

#endif