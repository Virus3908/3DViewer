#include "s21_controller.h"

namespace s21 {

Controller::Controller() : backend_(new Backend) {
  backend_->addObserver(this);  // Подписываемся на изменения в Backend
  backend_->notifyUpdate();
}

Controller::~Controller() {
  backend_->removeObserver(this);
  delete backend_;
}

Status_e Controller::loadModel(const std::string &fileName) {
  Status_e res = backend_->readModel(fileName);
  if (res == Status_e::OK) {
    backend_->notifyUpdate();
    clearTransformation();
    currentFileName = fileName;
  } else {
    backend_->readModel(currentFileName);
  }
  return res;
}

void Controller::applyTransformation(TransformationName_e transformation,
                                     bool isMouse, float direction) {
  backend_->updateTransformation(transformation, isMouse, direction);
  backend_->notifyUpdate();
}

void Controller::update() {
  transformation = backend_->getTransformationMatrix();
}

void Controller::onObservableDestruction() { backend_ = nullptr; }

const std::vector<Vertex_t> &Controller::getVertices() const {
  return backend_->getVertices();
}

const std::vector<Face_t> &Controller::getFaces() const {
  return backend_->getFaces();
}

const std::vector<Edge_t> &Controller::getEdges() const {
  return backend_->getEdges();
}

Matrix Controller::getTransformation() const { return transformation; }

void Controller::clearTransformation() {
  backend_->clearTransformation();
  backend_->notifyUpdate();
}

}  // namespace s21