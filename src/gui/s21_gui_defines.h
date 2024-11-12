/// @mainpage
/// @file s21_gui_defines.h
/// @author machelch
/// @brief 3D viewer
/// @version 1.0
/// @date 2024-11-12
///
/// @copyright Copyright (c) 2024

#ifndef S21_DEFINES_H
#define S21_DEFINES_H

#include <QApplication>
#include <QComboBox>
#include <QEvent>
#include <QFileDialog>
#include <QFontDatabase>
#include <QKeyEvent>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QMessageBox>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <QProgressBar>
#include <QPushButton>
#include <QSlider>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>
#include <QtGui>
#include <functional>
#include <thread>

#include "../controller/s21_controller.h"

/// @brief Размер меню по вертикали
#define MENU_WINDOW_H 150
/// @brief Размер меню по горизонтали
#define MENU_WINDOW_W 200

/// @brief Размер кнопки по вертикали
#define BUTTON_H 30
/// @brief Размер кнопки по горизонтали
#define BUTTON_W 170

/// @brief Ширина индикатора выполнения
#define PROGRESS_W 400
/// @brief Высота индикатора выполнения
#define PROGRESS_H 40

/// @brief Отступы между элементами
#define SPACING 20
/// @brief Отступы в настройках
#define SETTING_SPACING 5

/// @brief Высота окна
#define WINDOW_H 1000
/// @brief Ширина окна
#define WINDOW_W 1300

/// @brief Чувствительность поворота
#define SENSITIVITY_ROTATION 1.0f
/// @brief Чувствительность трансляции
#define SENSITIVITY_TRANSLATION 1.70f

/// @brief Цвет фона кнопки
#define BUTTON_BG_COLOR "rgb(97, 95, 137)"
/// @brief Цвет фона кнопки при нажатии
#define BUTTON_PRESSED_BG_COLOR "rgb(28, 27, 72)"
/// @brief Цвет фона кнопки при наведении
#define BUTTON_HOVER_BG_COLOR "rgb(47, 45, 90)"
/// @brief Цвет текста на кнопке
#define BUTTON_TEXT_COLOR "LightCyan"

/// @brief Количество кадров в секунду
#define FPS 10
/// @brief Длина видео в секундах
#define VIDEO_LEN 10

/// @brief Стиль кнопки
#define BUTTON_STYLE                           \
  "QPushButton{"                               \
  "border-radius: 5px;"                        \
  "border: 0px;"                               \
  "background-color: " BUTTON_BG_COLOR         \
  ";"                                          \
  "color: " BUTTON_TEXT_COLOR                  \
  ";"                                          \
  "font-size: 14px;"                           \
  "}"                                          \
  "QPushButton:pressed{"                       \
  "background-color: " BUTTON_PRESSED_BG_COLOR \
  "}"                                          \
  "QPushButton:hover{"                         \
  "background-color:" BUTTON_HOVER_BG_COLOR "}"

/// @brief Стиль для виджета QLineEdit
#define LINE_STYLE                   \
  "QLineEdit {"                      \
  "color: " LINE_COLOR_TEXT          \
  ";"                                \
  "background-color: " LINE_BG_COLOR \
  ";"                                \
  "border-radius: 5px;"              \
  "padding: 4px;"                    \
  "font-size: 14px;"                 \
  "}"

/// @brief Стиль для горизонтального слайдера QSlider
#define SLIDER_STYLE                        \
  "QSlider::handle:horizontal {"            \
  "    background-color:" BUTTON_TEXT_COLOR \
  ";"                                       \
  "    width: 10px;"                        \
  "    height: 10px;"                       \
  "    border-radius: 5px;"                 \
  "}"                                       \
  "QSlider::groove:horizontal {"            \
  "    height: 10px;"                       \
  "    background:" BUTTON_PRESSED_BG_COLOR \
  ";"                                       \
  "    margin: 3px 0;"                      \
  "    border-radius: 5px;"                 \
  "}"

/// @brief Стиль для выпадающего списка QComboBox
#define COMBOBOX_STYLE                                     \
  "QComboBox {"                                            \
  "    border-radius: 5px;"                                \
  "    border: 1px solid gray;"                            \
  "    background-color: " BUTTON_BG_COLOR                 \
  ";"                                                      \
  "    color: " BUTTON_TEXT_COLOR                          \
  ";"                                                      \
  "    font-size: 14px;"                                   \
  "    padding: 3px 8px;"                                  \
  "}"                                                      \
  "QComboBox::drop-down {"                                 \
  "    subcontrol-origin: padding;"                        \
  "    subcontrol-position: top right;"                    \
  "    width: 15px;"                                       \
  "    border-left: 1px solid darkgray;"                   \
  "}"                                                      \
  "QComboBox::down-arrow {"                                \
  "    image: url(:/icons/arrow-down.png);"                \
  "    width: 12px;"                                       \
  "    height: 12px;"                                      \
  "}"                                                      \
  "QComboBox QAbstractItemView {"                          \
  "    border: 1px solid " BUTTON_PRESSED_BG_COLOR         \
  ";"                                                      \
  "    selection-background-color: " BUTTON_HOVER_BG_COLOR \
  ";"                                                      \
  "    padding: 5px;"                                      \
  "}"

/// @brief Стиль для отображения цвета с закругленными краями
#define DISPLAY_COLOR_STYLE \
  "border-radius: 10px;"    \
  "border: 3px solid " BUTTON_HOVER_BG_COLOR ";"

/// @brief Стиль для текста QLabel
#define LABEL_STYLE  \
  "font-size: 18px;" \
  "color:" BUTTON_TEXT_COLOR ";"

/// @brief Стиль для информационных меток QLabel
#define LABEL_STYLE_INFO \
  "font-size: 12px;"     \
  "color:" BUTTON_TEXT_COLOR ";"

/// @brief Цвет фона основного виджета
#define BG_COLOR "rgb(70, 68, 114);"

/// @brief Стиль фона основного виджета
#define MAIN_BG_STYLESHEET "background-color:" BG_COLOR

/// @brief Стиль для активного виджета
#define ACTING_BG_STYLESHEET      \
  "QWidget {"                     \
  "   background-color:" BG_COLOR \
  ";"                             \
  "   border-radius: 15px;"       \
  "}"

/// @brief Стиль для QProgressBar
#define PROGRESS_STYLE                            \
  "QProgressBar {"                                \
  "   border:" BUTTON_HOVER_BG_COLOR              \
  ";"                                             \
  "   border-radius: 15px;"                       \
  "   background-color:" BUTTON_BG_COLOR          \
  ";"                                             \
  "   text-align: center;"                        \
  "   font-size: 32px;"                           \
  "}"                                             \
  "QProgressBar::chunk {"                         \
  "   background-color: " BUTTON_PRESSED_BG_COLOR \
  ";"                                             \
  "   border-radius: 15px;"                       \
  "}"

/// @brief Высота слайдера
#define SLIDER_H_SIZE 30
/// @brief Ширина слайдера
#define SLIDER_W_SIZE 100

/// @brief Высота линии
#define LINE_H_SIZE SLIDER_H_SIZE
/// @brief Ширина линии
#define LINE_W_SIZE 40

/// @brief Высота метки
#define LABEL_H_SIZE SLIDER_H_SIZE - 10

/// @brief Ширина блока
#define BOX_W_SIZE 25

/// @brief Цвет текста для QLineEdit
#define LINE_COLOR_TEXT "LightCyan"
/// @brief Цвет фона для QLineEdit
#define LINE_BG_COLOR "rgb(28, 27, 72)"

#endif