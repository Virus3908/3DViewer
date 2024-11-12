#include <QApplication>
#include <QDir>

#include "s21_frontend.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  Q_INIT_RESOURCE(resources);

  QSurfaceFormat format;
  format.setVersion(2, 1);
  format.setProfile(QSurfaceFormat::NoProfile);
  QSurfaceFormat::setDefaultFormat(format);

  s21::MainWindow viewer;
  viewer.setWindowTitle("3D Viewer");
  viewer.show();
  return app.exec();
}
