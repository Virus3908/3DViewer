/// @mainpage
/// @file s21_viewer_widget.h
/// @author machelch
/// @brief 3D viewer
/// @version 1.0
/// @date 2024-11-12
///
/// @copyright Copyright (c) 2024

#ifndef S21_OPENGL_H
#define S21_OPENGL_H

// OPENGL v2.1

#include "../s21_gui_defines.h"

namespace s21 {

/// @brief Класс openGL
class ViewerWidget : public QOpenGLWidget, protected QOpenGLFunctions {
 public:
  /// @brief конструктор
  /// @param parent указатель на родительский виджет
  /// @param set Указатель на настройки
  explicit ViewerWidget(QWidget *parent = nullptr, QSettings *set = nullptr);
  /// @brief деструктор
  ~ViewerWidget();

  /// @brief Загрузка модели
  /// @param pathToFile путь к файлу
  /// @return Статус загрузки модели
  Status_e loadModel(QString pathToFile);
  /// @brief сделать скриншот
  /// @return изображение
  QImage takeScreenshot();
  /// @brief сброс трансформации
  void resetTransformation();
  /// @brief трансформация
  /// @param transformation тип трансформации
  /// @param delta на сколько трансформация
  void transformation(TransformationName_e transformation, float delta);
  /// @brief получение размера вектора вершин
  /// @return кол-во вершин
  std::size_t getVerticesSize();
  /// @brief получение размера вектора ребер
  /// @return кол-во ребер
  std::size_t getEdgesSize();

 protected:
  /// @brief нажатие на кнопку мыши
  /// @param event событие
  void mousePressEvent(QMouseEvent *event) override;
  /// @brief перемещение мышки
  /// @param event событие
  void mouseMoveEvent(QMouseEvent *event) override;
  /// @brief отжатие кнопки мыши
  /// @param event событие
  void mouseReleaseEvent(QMouseEvent *event) override;
  /// @brief скролл колесика
  /// @param event событие
  void wheelEvent(QWheelEvent *event) override;

 protected:
  /// @brief Инициализация openGL
  void initializeGL() override;
  /// @brief Отрисовка opengl
  void paintGL() override;
  /// @brief изменения окна с opengl
  /// @param w ширина
  /// @param h высота
  void resizeGL(int w, int h) override;

 private:
  /// @brief Получить текущую матрицу трансформации.
  /// @return Объект QMatrix4x4, представляющий текущую трансформацию.
  QMatrix4x4 getTransformation();
  /// @brief Инициализирует шейдерную программу для использования в OpenGL.
  void initializeShader();
  /// @brief Обновляет матрицу трансформации объекта.
  void updateTransformation();
  /// @brief Устанавливает проекцию для отображения сцены.
  void setProjection();
  /// @brief Отрисовывает вершины на экране с использованием текущих настроек.
  void drawVertices();
  /// @brief Отрисовывает рёбра на экране с использованием текущих настроек.
  void drawEdges();
  /// @brief Программа шейдера для отрисовки объектов.
  QOpenGLShaderProgram *shaderProgram = nullptr;
  /// @brief Идентификатор буфера вершин для OpenGL.
  GLuint VBO;
  /// @brief Идентификатор буфера элементов для OpenGL.
  GLuint EBO;
  /// @brief Матрица трансформации для управления положением и ориентацией
  /// объекта.
  QMatrix4x4 transformationMatrix;
  /// @brief Контроллер, управляющий данными и логикой приложения.
  Controller *controller = nullptr;
  /// @brief Флаг, указывающий, производится ли в данный момент перетаскивание
  /// мышью.
  bool isDragging = false;
  /// @brief Последняя позиция курсора мыши для отслеживания перетаскивания.
  QPointF lastMousePos;
  /// @brief Указатель на объект QSettings для управления настройками
  /// приложения.
  QSettings *settings = nullptr;
};

}  // namespace s21

#endif