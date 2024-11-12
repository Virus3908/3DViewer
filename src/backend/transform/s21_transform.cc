#include "s21_transform.h"

namespace s21 {

TranslationXStrategy::TranslationXStrategy(float x) : tx(x) {}

Matrix TranslationXStrategy::applyTransformation() const {
  Matrix translation(4, 4);
  translation.setIdentity();
  translation[0][3] = tx;
  translation[1][3] = 0;
  translation[2][3] = 0;
  return translation;
}

TranslationYStrategy::TranslationYStrategy(float y) : ty(y) {}

Matrix TranslationYStrategy::applyTransformation() const {
  Matrix translation(4, 4);
  translation.setIdentity();
  translation[0][3] = 0;
  translation[1][3] = ty;
  translation[2][3] = 0;
  return translation;
}

TranslationZStrategy::TranslationZStrategy(float z) : tz(z) {}

Matrix TranslationZStrategy::applyTransformation() const {
  Matrix translation(4, 4);
  translation.setIdentity();
  translation[0][3] = 0;
  translation[1][3] = 0;
  translation[2][3] = tz;
  return translation;
}

ScaleStrategy::ScaleStrategy(float s) : sAll(s) {}

Matrix ScaleStrategy::applyTransformation() const {
  Matrix scale(4, 4);
  float scaleFactor = 1 + sAll;
  if (scaleFactor <= 0) {
    scaleFactor = 0.1f;
  }
  scale.setIdentity();
  scale[0][0] = scaleFactor;
  scale[1][1] = scaleFactor;
  scale[2][2] = scaleFactor;
  return scale;
}

RotateXStrategy::RotateXStrategy(float angle)
    : cosA(round(std::cos((angle * M_PI / 180.0f)) * 10e6) / 10e6),
      sinA(round(std::sin((angle * M_PI / 180.0f)) * 10e6) / 10e6) {}

Matrix RotateXStrategy::applyTransformation() const {
  Matrix rotate(4, 4);
  rotate.setIdentity();
  rotate[1][1] = cosA;
  rotate[1][2] = -sinA;
  rotate[2][1] = sinA;
  rotate[2][2] = cosA;
  return rotate;
}

RotateYStrategy::RotateYStrategy(float angle)
    : cosA(round(std::cos((angle * M_PI / 180.0f)) * 10e6) / 10e6),
      sinA(round(std::sin((angle * M_PI / 180.0f)) * 10e6) / 10e6) {}

Matrix RotateYStrategy::applyTransformation() const {
  Matrix rotate(4, 4);
  rotate.setIdentity();
  rotate[0][0] = cosA;
  rotate[0][2] = sinA;
  rotate[2][0] = -sinA;
  rotate[2][2] = cosA;
  return rotate;
}

RotateZStrategy::RotateZStrategy(float angle)
    : cosA(round(std::cos((angle * M_PI / 180.0f)) * 10e6) / 10e6),
      sinA(round(std::sin((angle * M_PI / 180.0f)) * 10e6) / 10e6) {}

Matrix RotateZStrategy::applyTransformation() const {
  Matrix rotate(4, 4);
  rotate.setIdentity();
  rotate[0][0] = cosA;
  rotate[0][1] = -sinA;
  rotate[1][0] = sinA;
  rotate[1][1] = cosA;
  return rotate;
}

TransformationContext::TransformationContext(
    TransformationStrategy *initStrategy)
    : strategy(initStrategy) {}

TransformationContext::~TransformationContext() { delete strategy; }

void TransformationContext::setStrategy(TransformationStrategy *newStrategy) {
  delete strategy;
  strategy = newStrategy;
}

Matrix TransformationContext::applyTransformation() const {
  Matrix transformation(4, 4);
  transformation.setIdentity();
  if (strategy) {
    transformation = strategy->applyTransformation();
  }
  return transformation;
}

}  // namespace s21