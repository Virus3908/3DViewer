/// @mainpage
/// @file s21_control_widget.h
/// @author machelch
/// @brief 3D viewer
/// @version 1.0
/// @date 2024-11-12
///
/// @copyright Copyright (c) 2024

#ifndef S21_NAVIGATION_H
#define S21_NAVIGATION_H

#include "../s21_frontend.h"
#include "../s21_gui_defines.h"
#include "s21_settings_widget.h"

namespace s21 {

/// @brief Класс виджета управления
class ControlWidget : public QWidget {
  Q_OBJECT
 public:
  /// @brief Конструктор виджета управления
  /// @param parent Родительский виджет
  /// @param set Указатель на настройки
  explicit ControlWidget(QWidget *parent = nullptr, QSettings *set = nullptr);
  /// @brief Деструктор виджета
  ~ControlWidget();

  /// @brief Установка трансформаций в ноль
  void setToDefault();

 signals:
  /// @brief Сигнал изменения настроек
  void settingsChanged();
  /// @brief Сигнал о смене виджета настроек
  /// @param newWidget Указатель на виджет настроек
  void switchToNewWidget(QWidget *newWidget);

 private:
  /// @brief Создание кнопок виджета
  void createButtons();
  /// @brief Создание кнопки
  /// @param text Текст на кнопке
  /// @return Указатель на новую кнопку
  QPushButton *createButton(const QString &text);

  /// @brief Создание layout
  void createLayout();

  /// @brief Связывание сигналов виджета с родительским виджетом и кнопок с
  /// методами
  void initSignals();

  /// @brief Нажатие на кнопку фона
  void backgroundSettingsPressed();
  /// @brief Нажатие на кнопку вершин
  void verticesSettingsPressed();
  /// @brief Нажатие на кнопку ребер
  void edgesSettingsPressed();
  /// @brief Нажатие на кнопку перемещения
  void translatePressed();
  /// @brief Нажатие на кнопку масштабирования
  void scalePressed();
  /// @brief Нажатие на кнопку вращения
  void rotatePressed();

  /// @brief Указатель на настройки
  QSettings *settings;
  /// @brief Указатель на кнопку фона
  QPushButton *backgroundSettingsButton = nullptr;
  /// @brief Указатель на кнопку вершин
  QPushButton *verticesSettingsButton = nullptr;
  /// @brief Указатель на кнопку ребер
  QPushButton *edgesSettingsButton = nullptr;
  /// @brief Указатель на кнопку перемещения
  QPushButton *translateButton = nullptr;
  /// @brief Указатель на кнопку масштабирования
  QPushButton *scaleButton = nullptr;
  /// @brief Указатель на кнопку вращения
  QPushButton *rotateButton = nullptr;
  /// @brief Численные значения трансформаций уже применённых к модели
  int translateX, translateY, translateZ, scale, rotateX, rotateY, rotateZ;
};

}  // namespace s21

#endif