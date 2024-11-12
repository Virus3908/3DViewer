#include "s21_viewer_widget.h"

namespace s21 {

ViewerWidget::ViewerWidget(QWidget* parent, QSettings* set)
    : QOpenGLWidget{parent}, settings(set) {
  controller = new Controller();
  this->setMinimumSize(1000, 1000);
}

ViewerWidget::~ViewerWidget() {
  delete controller;
  controller = nullptr;
  if (shaderProgram) {
    delete shaderProgram;
    shaderProgram = nullptr;
  }
  if (VBO != 0) {
    glDeleteBuffers(1, &VBO);
    VBO = 0;
  }
  if (EBO != 0) {
    glDeleteBuffers(1, &EBO);
    EBO = 0;
  }
}

void ViewerWidget::initializeGL() {
  initializeOpenGLFunctions();

  initializeShader();

  glEnable(GL_DEPTH_TEST);
}

void ViewerWidget::initializeShader() {
  shaderProgram = new QOpenGLShaderProgram(this);
  shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                         ":/shaders/vertex_shader.glsl");
  shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                         ":/shaders/fragment_shader.glsl");
  if (!shaderProgram->link()) {
    qDebug() << "Ошибка связывания шейдерной программы:"
             << shaderProgram->log();
  }
}

Status_e ViewerWidget::loadModel(QString pathToFile) {
  Status_e status = controller->loadModel(pathToFile.toStdString());
  if (status == Status_e::OK) {
    if (VBO != 0) {
      glDeleteBuffers(1, &VBO);
      VBO = 0;
    }
    if (EBO != 0) {
      glDeleteBuffers(1, &EBO);
      EBO = 0;
    }

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, (getVerticesSize()) * sizeof(Vertex_t),
                 controller->getVertices().data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, getEdgesSize() * sizeof(Edge_t),
                 controller->getEdges().data(), GL_STATIC_DRAW);
  }
  return status;
}

void ViewerWidget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void ViewerWidget::paintGL() {
  glClearColor(settings->value("backgroundColorRed").toInt() / 255.0f,
               settings->value("backgroundColorGreen").toInt() / 255.0f,
               settings->value("backgroundColorBlue").toInt() / 255.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  updateTransformation();

  shaderProgram->bind();
  shaderProgram->setUniformValue("mvp_matrix", transformationMatrix);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

  GLint posAttrib = shaderProgram->attributeLocation("vertex_pos");
  glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex_t),
                        nullptr);
  glEnableVertexAttribArray(posAttrib);

  drawEdges();
  if (settings->value("verticesStyle").toInt()) drawVertices();

  glDisableVertexAttribArray(posAttrib);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  shaderProgram->release();
}

void ViewerWidget::updateTransformation() {
  transformationMatrix.setToIdentity();
  setProjection();
  transformationMatrix.translate(0.0f, 0.0f, -2.0f);
  transformationMatrix *= getTransformation();
}

void ViewerWidget::setProjection() {
  float aspect = static_cast<float>(width()) / height();
  float nearPlane = 0.1f;
  float farPlane = 100.0f;
  float fov = 45.0f;

  float top = tan((fov * M_PI / 360.0)) * nearPlane;
  float bottom = -top;
  float right = top * aspect;
  float left = -right;

  if (settings->value("isOrtho").toBool()) {
    float aspectRatio = static_cast<float>(width()) / height();
    transformationMatrix.ortho(-aspectRatio, aspectRatio, -1.0, 1.0, -1.0,
                               100.0);
  } else {
    transformationMatrix.frustum(left, right, bottom, top, nearPlane, farPlane);
  }
}

void ViewerWidget::drawVertices() {
  if (settings->value("verticesStyle").toInt() == 1) {
    glEnable(GL_POINT_SMOOTH);
  } else {
    glDisable(GL_POINT_SMOOTH);
  }
  shaderProgram->setUniformValue("isLine", false);
  glPointSize(settings->value("verticesSize").toInt() / 2.0f);
  shaderProgram->setUniformValue(
      "color",
      QVector4D(settings->value("verticesColorRed").toInt() / 255.0f,
                settings->value("verticesColorGreen").toInt() / 255.0f,
                settings->value("verticesColorBlue").toInt() / 255.0f, 1));

  glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>(getVerticesSize()));
}

void ViewerWidget::drawEdges() {
  if (settings->value("edgesStyle").toInt()) {
    shaderProgram->setUniformValue("isDashed", true);
  } else {
    shaderProgram->setUniformValue("isDashed", false);
  }
  shaderProgram->setUniformValue("isLine", true);
  glLineWidth(settings->value("edgesSize").toInt() / 10.0f);
  shaderProgram->setUniformValue(
      "color",
      QVector4D(settings->value("edgesColorRed").toInt() / 255.0f,
                settings->value("edgesColorGreen").toInt() / 255.0f,
                settings->value("edgesColorBlue").toInt() / 255.0f, 1));
  glDrawElements(GL_LINES, getEdgesSize() * 2, GL_UNSIGNED_INT, nullptr);
  glDisable(GL_LINE_STIPPLE);
}

void ViewerWidget::mousePressEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    lastMousePos = event->position();
    isDragging = true;
  }
  QWidget::mousePressEvent(event);
}

void ViewerWidget::mouseMoveEvent(QMouseEvent* event) {
  if (isDragging) {
    QPointF currentMousePos = event->position();
    if (event->modifiers()) {
      controller->applyTransformation(
          TransformationName_e::TranslationX, true,
          +(currentMousePos.x() - lastMousePos.x()) / width() *
              SENSITIVITY_TRANSLATION *
              (settings->value("isOrtho").toBool() ? 1 : 1.1));
      controller->applyTransformation(
          TransformationName_e::TranslationY, true,
          -(currentMousePos.y() - lastMousePos.y()) / height() *
              SENSITIVITY_TRANSLATION *
              (settings->value("isOrtho").toBool() ? 1 : 1.1));
    } else {
      controller->applyTransformation(
          TransformationName_e::RotateY, true,
          (currentMousePos.x() - lastMousePos.x()) * SENSITIVITY_ROTATION);
      controller->applyTransformation(
          TransformationName_e::RotateX, true,
          (currentMousePos.y() - lastMousePos.y()) * SENSITIVITY_ROTATION);
    }
    lastMousePos = currentMousePos;
    update();
  }
}

void ViewerWidget::mouseReleaseEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    isDragging = false;
  }
}

void ViewerWidget::wheelEvent(QWheelEvent* event) {
  float zoomFactor = (event->angleDelta().y()) / 100.0f;
  if (zoomFactor != 0) {
    float offsetX = -(event->position().x() - width() / 2.0f) / width();
    float offsetY = (event->position().y() - height() / 2.0f) / height();
    controller->applyTransformation(
        TransformationName_e::TranslationX, true,
        offsetX * zoomFactor * SENSITIVITY_TRANSLATION *
            (settings->value("isOrtho").toBool() ? 1 : 1.1));
    controller->applyTransformation(
        TransformationName_e::TranslationY, true,
        offsetY * zoomFactor * SENSITIVITY_TRANSLATION *
            (settings->value("isOrtho").toBool() ? 1 : 1.1));
    controller->applyTransformation(TransformationName_e::Scale, true,
                                    zoomFactor);
  }
  update();
}

void ViewerWidget::resetTransformation() {
  controller->clearTransformation();
  update();
}

void ViewerWidget::transformation(TransformationName_e transformation,
                                  float delta) {
  controller->applyTransformation(transformation, false, delta);
  update();
}

QMatrix4x4 ViewerWidget::getTransformation() {
  Matrix transf = controller->getTransformation();
  QMatrix4x4 qTransformation =
      QMatrix4x4(transf[0][0], transf[0][1], transf[0][2], transf[0][3],
                 transf[1][0], transf[1][1], transf[1][2], transf[1][3],
                 transf[2][0], transf[2][1], transf[2][2], transf[2][3],
                 transf[3][0], transf[3][1], transf[3][2], transf[3][3]);

  return qTransformation;
}

std::size_t ViewerWidget::getVerticesSize() {
  return controller->getVertices().size();
}

std::size_t ViewerWidget::getEdgesSize() {
  return controller->getEdges().size();
}

QImage ViewerWidget::takeScreenshot() {
  return grabFramebuffer().convertToFormat(QImage::Format_RGB32);
}

}  // namespace s21