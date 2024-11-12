/// @mainpage
/// @file s21_information_widget.h
/// @author machelch
/// @brief 3D viewer
/// @version 1.0
/// @date 2024-11-12
///
/// @copyright Copyright (c) 2024

#ifndef S21_INFORMATION_WIDGET_H
#define S21_INFORMATION_WIDGET_H

#include "../s21_gui_defines.h"

namespace s21 {

/// @brief Вилдет с информацией
class InformationWidget : public QWidget {
  Q_OBJECT
 public:
  /// @brief конструктор базовый
  /// @param parent указатель на родителя
  InformationWidget(QWidget *parent);
  /// @brief деструктор
  ~InformationWidget();

  /// @brief обновление информации о детале
  /// @param file имя файла
  /// @param vertices кол-во вершин
  /// @param edges кол-во ребер
  void updateInformation(QString file, std::size_t vertices, std::size_t edges);

 private:
  /// @brief Инициализация текста
  void initLabels();
  /// @brief Инициализация выкладки
  void initLayout();
  /// @brief Создания текста
  /// @param text ссылка на текст
  /// @return Указатель на новый текст
  QLabel *createLabel(const QString &text);

  /// @brief текст: имя модели
  QLabel *fileNameText = nullptr;
  /// @brief имя
  QLabel *fileName = nullptr;
  /// @brief текст: кол-во вершин
  QLabel *verticesText = nullptr;
  /// @brief кол-во вершин
  QLabel *verticesCount = nullptr;
  /// @brief текст кол-во ребер
  QLabel *edgesText = nullptr;
  /// @brief кол-во ребер
  QLabel *edgesCount = nullptr;
};
}  // namespace s21

#endif