/// @mainpage
/// @file s21_menu_widget.h
/// @author machelch
/// @brief 3D viewer
/// @version 1.0
/// @date 2024-11-12
///
/// @copyright Copyright (c) 2024

#ifndef S21_MENU_WIDGET_H
#define S21_MENU_WIDGET_H

#include "../s21_frontend.h"
#include "../s21_gui_defines.h"

namespace s21 {
/// @brief класс меню
class MenuWidget : public QWidget {
  Q_OBJECT
 public:
  /// @brief Конструктор
  /// @param parent Указатель на родительское окно
  /// @param mainSettings Указатель на настройки
  explicit MenuWidget(QWidget *parent = nullptr,
                      QSettings *mainSettings = nullptr);
  /// @brief Деструктор
  ~MenuWidget();

 signals:

  /// @brief сегнал об открытии новой модели
  /// @param pathToFile путь до выбранного файла
  void openNewModel(QString pathToFile);
  /// @brief сигнал скриншота
  /// @param directory путь куда сохранять
  void screenshotSignal(QString directory);
  /// @brief сигнал записи видео
  /// @param directory путь куда сохранять
  void captureVideoSignal(QString directory);
  /// @brief Сигнал сброса трансформаций
  void resetTransformationPressed();
  /// @brief сигнал изменения настроек
  void settingsChanged();

 private:
  /// @brief создание кнопок
  void createButtons();
  /// @brief создание новой кнопки
  /// @param text текст на кнопке
  /// @return указатель на новую кнопку
  QPushButton *createButton(const QString &text);

  /// @brief Создание текстового поля
  void createPathLine();
  /// @brief Кнопка открыть нажата
  void openPressed();
  /// @brief нажатие на кнопку смены проекции
  void toggleProjectionPressed();
  /// @brief нажатие на кнопку скриншота
  void screenshotPressed();
  /// @brief нажатие на кнопку захвата видео
  void captureVideoPressed();

  /// @brief создание лэйаута
  void createLayout();
  /// @brief связывание сигналов с родительским виджетом
  void initSignals();

  /// @brief Указатель на кнопку открыть
  QPushButton *buttonOpenModel;
  /// @brief Указатель на кнопку смены прекции
  QPushButton *buttonToggleProjection;
  /// @brief Указатель на кнопку сброса трансформаций
  QPushButton *buttonReset;
  /// @brief Указатель на кнопку скриншота
  QPushButton *buttonScreenshot;
  /// @brief Указатель на кнопку записи видео
  QPushButton *buttonCaptureVideo;
  /// @brief Строку для ввода пути
  QLineEdit *pathLine;
  /// @brief Указатель на настройки
  QSettings *settings;
};

}  // namespace s21

#endif
