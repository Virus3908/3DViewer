#include "test.h"

TEST(Viewer, OK) {
  s21::Controller *controller = new s21::Controller();
  EXPECT_EQ(controller->loadModel("./tests/c.obj"), s21::Status_e::OK);
  controller->getEdges();
  controller->getVertices();
  controller->getFaces();
  EXPECT_EQ(1, 1);
  delete controller;
}

TEST(Viewer, EMPTY) {
  s21::Controller *controller = new s21::Controller();
  EXPECT_EQ(controller->loadModel("./tests/empty.obj"),
            s21::Status_e::EmptyFile);
  delete controller;
}

TEST(Viewer, CURRUPTED) {
  s21::Controller *controller = new s21::Controller();
  EXPECT_EQ(controller->loadModel("./tests/wrong.obj"),
            s21::Status_e::FileCurrupted);
  delete controller;
}

TEST(Viewer, READERROR) {
  s21::Controller *controller = new s21::Controller();
  EXPECT_EQ(controller->loadModel("./tests/a.obj"), s21::Status_e::ReadError);
  delete controller;
}

TEST(Viewer, TRANSLATE) {
  s21::Controller *controller = new s21::Controller();
  controller->applyTransformation(s21::TransformationName_e::TranslationX,
                                  false, 1);
  controller->applyTransformation(s21::TransformationName_e::TranslationY,
                                  false, 1);
  controller->applyTransformation(s21::TransformationName_e::TranslationZ,
                                  false, 1);
  controller->applyTransformation(s21::TransformationName_e::TranslationX,
                                  false, -1);
  controller->applyTransformation(s21::TransformationName_e::TranslationY,
                                  false, -1);
  controller->applyTransformation(s21::TransformationName_e::TranslationZ,
                                  false, -1);
  s21::Matrix mat(4, 4);
  mat.setIdentity();
  EXPECT_EQ(controller->getTransformation(), mat);
  delete controller;
}

TEST(Viewer, ROTATE) {
  s21::Controller *controller = new s21::Controller();
  controller->applyTransformation(s21::TransformationName_e::RotateX, true, 45);
  controller->applyTransformation(s21::TransformationName_e::RotateY, true, 45);
  controller->applyTransformation(s21::TransformationName_e::RotateZ, true, 45);
  controller->applyTransformation(s21::TransformationName_e::RotateZ, true,
                                  -45);
  controller->applyTransformation(s21::TransformationName_e::RotateY, true,
                                  -45);
  controller->applyTransformation(s21::TransformationName_e::RotateX, true,
                                  -45);
  s21::Matrix mat(4, 4);
  mat.setIdentity();
  EXPECT_EQ(controller->getTransformation(), mat);
  delete controller;
}

TEST(Viewer, SCALE) {
  s21::Controller *controller = new s21::Controller();
  controller->applyTransformation(s21::TransformationName_e::Scale, false, 1);
  controller->applyTransformation(s21::TransformationName_e::Scale, false,
                                  -0.5);
  s21::Matrix mat(4, 4);
  mat.setIdentity();
  EXPECT_EQ(controller->getTransformation(), mat);
  delete controller;
}

TEST(Viewer, RESET) {
  s21::Controller *controller = new s21::Controller();
  controller->applyTransformation(s21::TransformationName_e::Scale, false, 1);
  controller->clearTransformation();
  s21::Matrix mat(4, 4);
  mat.setIdentity();
  EXPECT_EQ(controller->getTransformation(), mat);
  delete controller;
}