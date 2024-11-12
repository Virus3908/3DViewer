/// @mainpage
/// @file s21_common.h
/// @author machelch
/// @brief 3D viewer
/// @version 1.0
/// @date 2024-11-12
///
/// @copyright Copyright (c) 2024

#ifndef S21_COMMON_H
#define S21_COMMON_H

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

/// @brief Минимальная точность для float
#define MY_EPS 1e-6

namespace s21 {

/// @brief Статусы прочтения файла
enum Status_e { OK, ReadError, EmptyFile, FileCurrupted };

/// @brief Структура точки
struct Vertex_t {
  /// @brief Позиция вдоль оси х
  float x;
  /// @brief Позиция вдоль оси y
  float y;
  /// @brief Позиция вдоль оси z
  float z;
  /// @brief Конструктор точки
  /// @param _x Положение по х
  /// @param _y Положение по у
  /// @param _z Положение по z
  Vertex_t(float _x = 0, float _y = 0, float _z = 0) : x(_x), y(_y), z(_z) {}
};

/// @brief Структура поверхности
struct Face_t {
  /// @brief Вектор с номерами вершин для поверхности
  std::vector<unsigned int> vertexIndex;
};

/// @brief Структура ребер
struct Edge_t {
  /// @brief Первая точка ребра
  unsigned int indFirst;
  /// @brief Вторая точка ребра
  unsigned int indSecond;
  /// @brief Конструктор ребра записываются строго в порядке возрастания точки
  /// @param first Первая точка
  /// @param second Вторая точка
  Edge_t(unsigned int first = 0, unsigned int second = 0)
      : indFirst(std::min(first, second)), indSecond(std::max(first, second)) {}

  // bool operator<(const Edge_t &other) const {
  //   return std::tie(indFirst, indSecond) <
  //          std::tie(other.indFirst, other.indSecond);
  // }
};

/// @brief Клас наблюдателя
class Observer {
 public:
  /// @brief Виртуальный деструктор стандартный
  virtual ~Observer() = default;
  /// @brief Обязательная перегрузка на обновления
  virtual void update() = 0;
  /// @brief Обязательная перегрузка удаления наблюдателя на удаление
  /// наблюдателя из наблюдаемых объектов
  virtual void onObservableDestruction() = 0;
};

/// @brief Клас наблюдаемого
class Observable {
 public:
  /// @brief Деструктор наблюдаемого
  ~Observable() {
    for (Observer *observer : _observers) {
      observer->onObservableDestruction();
    }
    _observers.clear();
  }

  /// @brief Добавление наблюдателя в векор наблюдателей
  /// @param observer Указатель на наблюдателя
  void addObserver(Observer *observer) { _observers.push_back(observer); }
  /// @brief Удаление наблюдателя
  /// @param observer Указатель на наблюдателя
  void removeObserver(Observer *observer) {
    _observers.erase(
        std::remove(_observers.begin(), _observers.end(), observer),
        _observers.end());
  }
  /// @brief Оповещение об обновлении наблюдателей
  void notifyUpdate() {
    int size = _observers.size();
    for (int i = 0; i < size; i++) {
      _observers[i]->update();
    }
  }

 private:
  /// @brief Вектор указателей на наблюдателей
  std::vector<Observer *> _observers;
};

}  // namespace s21

#endif