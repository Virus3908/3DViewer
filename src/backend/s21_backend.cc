#include "s21_backend.h"

namespace s21 {

Backend::Backend() {
  TransformationMatrix = Matrix(4, 4);
  TransformationMatrix.setIdentity();
}

void Backend::clearTransformation() { TransformationMatrix.setIdentity(); }

Status_e Backend::readModel(const std::string &fileName) {
  Status_e readingStatus = model.readFile(fileName);
  return readingStatus;
}

const std::vector<Vertex_t> &Backend::getVertices() {
  return model.getVertex();
}

const std::vector<Face_t> &Backend::getFaces() { return model.getFace(); }

const std::vector<Edge_t> &Backend::getEdges() { return model.getEdge(); }

const Matrix &Backend::getTransformationMatrix() {
  return TransformationMatrix;
}

void Backend::updateTransformation(TransformationName_e Transformation,
                                   bool isMouse, const float &direction) {
  Matrix tempTransfromMatrix;
  context.setStrategy(updateStrategy(Transformation, direction));

  if (isMouse) {
    tempTransfromMatrix = context.applyTransformation() * TransformationMatrix;
  } else {
    tempTransfromMatrix = TransformationMatrix * context.applyTransformation();
  }

  if (!isZeroTransform(tempTransfromMatrix)) {
    TransformationMatrix = tempTransfromMatrix;
  }
}

TransformationStrategy *Backend::updateStrategy(
    TransformationName_e Transformation, const float &direction) {
  TransformationStrategy *strategy = nullptr;
  switch (Transformation) {
    case TransformationName_e::TranslationX:
      strategy = new TranslationXStrategy(direction);
      break;
    case TransformationName_e::TranslationY:
      strategy = new TranslationYStrategy(direction);
      break;
    case TransformationName_e::TranslationZ:
      strategy = new TranslationZStrategy(direction);
      break;
    case TransformationName_e::Scale:
      strategy = new ScaleStrategy(direction);
      break;
    case TransformationName_e::RotateX:
      strategy = new RotateXStrategy(direction);
      break;
    case TransformationName_e::RotateY:
      strategy = new RotateYStrategy(direction);
      break;
    case TransformationName_e::RotateZ:
      strategy = new RotateZStrategy(direction);
      break;
    default:
      strategy = nullptr;
  }
  return strategy;
}

bool Backend::isZeroTransform(Matrix mat) {
  return !((std::abs(mat[0][0]) > 1e-15 && std::abs(mat[1][1]) > 1e-15 &&
            std::abs(mat[2][2]) > 1e-15) &&
           (std::abs(mat[0][0]) < 1e25 && std::abs(mat[1][1]) < 1e25 &&
            std::abs(mat[2][2]) < 1e25));
}

}  // namespace s21