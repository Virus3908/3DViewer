/// @mainpage
/// @file s21_settings_widget.h
/// @author machelch
/// @brief 3D viewer
/// @version 1.0
/// @date 2024-11-12
///
/// @copyright Copyright (c) 2024

#ifndef S21_SETTINGS_WIDGET_H
#define S21_SETTINGS_WIDGET_H

#include "../s21_frontend.h"
#include "../s21_gui_defines.h"

namespace s21 {

/// @brief Список возможных виджетов настроек
enum Settings_e {
  Background_e,
  Vertices_e,
  Edges_e,
  Translate_e,
  Scale_e,
  Rotate_e
};

/// @brief Класс виджета настроек
class SettingsWidget : public QWidget {
  Q_OBJECT
 public:
  /// @brief Конструктор виджета настроек
  /// @param parent указатель на родителя
  /// @param set Указатель на настройки
  /// @param t Тип виджета
  /// @param x указатель на перемещение
  /// @param y указатель на перемещение
  /// @param z указатель на перемещение
  SettingsWidget(QWidget *parent = nullptr, QSettings *set = nullptr,
                 const Settings_e &t = Settings_e::Background_e,
                 int *x = nullptr, int *y = nullptr, int *z = nullptr);
  /// @brief Деструктор
  ~SettingsWidget();

 signals:
  /// @brief сигнал об изменении настроек
  void settingsChanged();
  /// @brief Сигнал о трансформации
  /// @param transformation тип трансформации
  /// @param delta Изменение трансформации
  void changeTransformation(TransformationName_e transformation, float delta);

 private:
  /// @brief инициализация слайдеров
  void initSliders();
  /// @brief иницилизация комбобокса
  void initComboBox();
  /// @brief инициализация текста
  void initText();
  /// @brief инициализация текстов цветовых слайдеров
  void initColorText();
  /// @brief инициализация текстов трансформ слайдеров
  void initTransformText();
  /// @brief связывание сигналов
  void initSignals();

  /// @brief Конструктор сладера
  /// @return Указатель на новый виджет слайдер
  QSlider *createSlider();
  /// @brief Конструктор лайнедит
  /// @return указатель на новый виджет строку
  QLineEdit *createLine();
  /// @brief Конструктор текста
  /// @param text ссылка на текст
  /// @return указатель на новый текстовый виджет
  QLabel *createLabel(const QString &text);
  /// @brief Конструктор комбобокса
  /// @return указатель на новый виджет комбобокс
  QComboBox *createComboBox();

  /// @brief Обновление виджета цвета
  void updateDisplayColor();

  /// @brief Выбор какие слайдеры будут
  void setupSliders();
  /// @brief Слайдер вершин
  void verticesSliders();
  /// @brief Слайдер фона
  void backgroundSlides();
  /// @brief слайдер ребер
  void edgesSliders();
  /// @brief слайдер перемещения
  void translateSlider();
  /// @brief слайдер масштабирования
  void scaleSliders();
  /// @brief слайдер вращения
  void rotateSliders();

  /// @brief коннект слайдеров
  /// @param slider указатель на слайдер
  /// @param line указатель на лайнедит
  /// @param key Ключ настроек
  /// @param min Минимальное значение
  /// @param max Максимальное значение
  void connectSlider(QSlider *slider, QLineEdit *line, const QString &key,
                     const int &min, const int &max);

  /// @brief коннект слайдеров
  /// @param slider указатель на слайдер
  /// @param line указатель на лайнедит
  /// @param val нынешнее значение
  /// @param min минимум
  /// @param max максимум
  /// @param modifier Коэфицииент
  /// @param transformation Тип трансформации
  void connectSlider(QSlider *slider, QLineEdit *line, int *val, const int &min,
                     const int &max, const int &modifier,
                     const TransformationName_e &transformation);

  /// @brief Создание комбобокса
  void setupComboBox();
  /// @brief комбобокс вершин
  void verticesComboBox();
  /// @brief комбобокс ребер
  void edgesComboBox();
  /// @brief коннект комбобокса
  /// @param box указатель на комбобокс
  /// @param key ключ из настроек
  void connectComboBox(QComboBox *box, const QString &key);
  /// @brief создание выкладки виджетов
  void createLayout();
  /// @brief Сбор 3 виджетов в 1 лэйаут
  /// @param text Текст
  /// @param slider Слайдер
  /// @param line ЛайнЕдит
  /// @return Возвращает указатель на layout
  QHBoxLayout *addSliderToLayout(QLabel *text, QSlider *slider,
                                 QLineEdit *line);

  /// @brief тип виджета
  Settings_e type;
  /// @brief Виджет фона
  QWidget *container = nullptr;
  /// @brief слайдер
  QSlider *sliderFirst = nullptr;
  /// @brief слайдер
  QSlider *sliderSecond = nullptr;
  /// @brief слайдер
  QSlider *sliderThird = nullptr;
  /// @brief слайдер
  QSlider *sliderFourth = nullptr;
  /// @brief лайнедит
  QLineEdit *lineFirst = nullptr;
  /// @brief лайнедит
  QLineEdit *lineSecond = nullptr;
  /// @brief лайнедит
  QLineEdit *lineThird = nullptr;
  /// @brief лайнедит
  QLineEdit *lineFourth = nullptr;
  /// @brief комбобокс
  QComboBox *comboBox = nullptr;
  /// @brief Виджет с активным цветом
  QWidget *displayColor = nullptr;
  /// @brief указатель на настройки
  QSettings *settings = nullptr;
  /// @brief текст
  QLabel *textFirst = nullptr;
  /// @brief текст
  QLabel *textSecond = nullptr;
  /// @brief текст
  QLabel *textThird = nullptr;
  /// @brief текст
  QLabel *textFourth = nullptr;
  /// @brief текст
  QLabel *mainText = nullptr;
  /// @brief Указатель на значения перемещений
  int *first, *second, *third;
};

}  // namespace s21

#endif