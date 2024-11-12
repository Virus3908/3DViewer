/// @mainpage
/// @file s21_frontend.h
/// @author machelch
/// @brief 3D viewer
/// @version 1.0
/// @date 2024-11-12
///
/// @copyright Copyright (c) 2024

#ifndef S21_FRONTEND_H
#define S21_FRONTEND_H

#include <opencv2/opencv.hpp>

#include "OpenGL/s21_viewer_widget.h"
#include "control/s21_control_widget.h"
#include "infortmation/s21_information_widget.h"
#include "menu/s21_menu_widget.h"
#include "s21_gui_defines.h"

namespace s21 {

/// @brief Класс основного окна
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  /// @brief Базовый конструктор
  explicit MainWindow();
  /// @brief Базоывй деструктор
  ~MainWindow();

 public slots:
  /// @brief Открывает 3D-модель из указанного файла.
  /// @param pathToFile Путь к файлу с моделью.
  void openModel(QString pathToFile);
  /// @brief Сохраняет текущий кадр сцены в виде изображения в указанной
  /// директории.
  /// @param directory Директория для сохранения скриншота.
  void captureScreenshot(QString directory);
  /// @brief Запускает захват видеозаписи текущей сцены и сохраняет её в
  /// указанной директории.
  /// @param directory Директория для сохранения видео.
  void captureVideo(QString directory);
  /// @brief Сбрасывает текущие трансформации объекта, возвращая его в исходное
  /// состояние.
  void resetTransformation();
  /// @brief Обновляет текущие настройки виджета на основе новых данных.
  void updateFromSettings();
  /// @brief Устанавливает новый виджет в интерфейсе.
  /// @param newWidget Указатель на новый виджет.
  void setNewWidget(QWidget *newWidget);
  /// @brief Обновляет трансформацию объекта с указанным типом трансформации и
  /// значением.
  /// @param transformation Тип трансформации.
  /// @param delta Величина изменения для трансформации.
  void updateTransformation(TransformationName_e transformation, float delta);

 protected:
  /// @brief Обрабатывает событие нажатия кнопки мыши на виджете.
  /// @param event Указатель на событие нажатия мыши.
  void mousePressEvent(QMouseEvent *event) override;

 private:
  /// @brief Инициализирует компоновку основного окна.
  void initLayout();
  /// @brief Инициализирует настройки приложения.
  void initSettings();
  /// @brief Отображает сообщение об ошибке в зависимости от переданного
  /// статуса открытия модели
  /// @param status Статус, указывающий тип ошибки.
  void showErrorMessage(Status_e status);
  /// @brief Создает видеофайл из собранных кадров.
  void createVideo();
  /// @brief Захватывает текущий кадр и добавляет его в видеопоследовательность.
  void captureFrame();
  /// @brief Настраивает и отображает индикатор выполнения.
  void setupProgressBar();

  /// @brief Указатель на центральный виджет основного окна.
  QWidget *centralWidget = nullptr;
  /// @brief Указатель на виджет меню.
  QWidget *menuWidget = nullptr;
  /// @brief Указатель на виджет управления.
  QWidget *controlWidget = nullptr;
  /// @brief Указатель на текущий виджет настроек.
  QWidget *actingWidget = nullptr;
  /// @brief Указатель на виджет с информацией.
  QWidget *informationWidget = nullptr;
  /// @brief Указатель на виджет для отображения 3D-сцены.
  ViewerWidget *fieldWidget = nullptr;
  /// @brief Указатель на кнопку выхода.
  QPushButton *exitButton = nullptr;
  /// @brief Указатель на индикатор выполнения.
  QProgressBar *progressBar = nullptr;
  /// @brief Указатель на таймер для захвата кадров.
  QTimer *timer = nullptr;
  /// @brief Объект настроек приложения.
  QSettings settings;
  /// @brief Путь к файлу видеозаписи.
  QString videoPathFile;
  /// @brief Вектор кадров для создания видео.
  std::vector<QImage> frames;
};

}  // namespace s21
#endif  // S21_FRONTEND_H
