#include "s21_frontend.h"

namespace s21 {

MainWindow::MainWindow() {
  QCoreApplication::setOrganizationName("s21");
  QCoreApplication::setApplicationName("3D_Viewer");
  initSettings();

  centralWidget = new QWidget(this);
  centralWidget->setStyleSheet(MAIN_BG_STYLESHEET);

  menuWidget = new MenuWidget(this, &settings);
  informationWidget = new InformationWidget(this);
  controlWidget = new ControlWidget(this, &settings);

  exitButton = new QPushButton("Exit", this);
  exitButton->setStyleSheet(BUTTON_STYLE);
  exitButton->setFixedSize(BUTTON_W, BUTTON_H);
  connect(exitButton, &QPushButton::clicked, qApp, &QApplication::quit);

  timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &MainWindow::captureFrame);

  fieldWidget = new ViewerWidget(this, &settings);

  initLayout();

  setCentralWidget(centralWidget);
}

void MainWindow::initLayout() {
  QHBoxLayout *layoutH = new QHBoxLayout(centralWidget);
  QVBoxLayout *layoutV = new QVBoxLayout;
  layoutV->addWidget(menuWidget, 1, Qt::AlignCenter);
  layoutV->addWidget(informationWidget, 0);
  layoutV->addWidget(controlWidget, 1, Qt::AlignCenter);
  layoutV->addWidget(exitButton, 1, Qt::AlignCenter);
  layoutH->addLayout(layoutV);
  layoutH->addWidget(fieldWidget);
  layoutH->setSpacing(0);
  layoutH->setContentsMargins(0, 0, 0, 0);
}

MainWindow::~MainWindow() {
  if (actingWidget) actingWidget->deleteLater();
  if (menuWidget) menuWidget->deleteLater();
  if (controlWidget) controlWidget->deleteLater();
  if (fieldWidget) fieldWidget->deleteLater();
  if (centralWidget) centralWidget->deleteLater();
  if (exitButton) exitButton->deleteLater();
  if (timer) timer->deleteLater();
  if (progressBar) progressBar->deleteLater();
}

void MainWindow::openModel(QString pathToFile) {
  Status_e status = fieldWidget->loadModel(pathToFile);
  if (actingWidget) {
    actingWidget->deleteLater();
    actingWidget = nullptr;
  }
  if (status == Status_e::OK) {
    fieldWidget->update();
    qobject_cast<InformationWidget *>(informationWidget)
        ->updateInformation(pathToFile, fieldWidget->getVerticesSize(),
                            fieldWidget->getEdgesSize());
  } else {
    showErrorMessage(status);
  }
  qobject_cast<ControlWidget *>(controlWidget)->setToDefault();
  fieldWidget->update();
}

void MainWindow::captureScreenshot(QString directory) {
  if (!directory.endsWith('/')) {
    directory += '/';
  }
  QString pathToFile =
      directory + "screenshot_" +
      QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + ".png";
  fieldWidget->takeScreenshot().save(pathToFile, "PNG");
}

void MainWindow::captureVideo(QString directory) {
  if (!directory.endsWith('/')) {
    directory += '/';
  }
  videoPathFile = directory + "video_" +
                  QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") +
                  ".avi";
  frames.clear();
  timer->start(1000 / FPS);
}

void MainWindow::captureFrame() {
  frames.push_back(fieldWidget->grabFramebuffer());
  if (frames.size() >= FPS * VIDEO_LEN) {
    timer->stop();
    createVideo();
    QMessageBox msgBox;
    msgBox.setText("Done");
    msgBox.exec();
  }
}

void MainWindow::showErrorMessage(Status_e status) {
  QString errorMessage;
  QMessageBox msgBox;
  switch (status) {
    case Status_e::ReadError:
      errorMessage = QString("Файл не выбран");
      break;
    case Status_e::EmptyFile:
      errorMessage = QString("Пустой файл");
      break;
    case Status_e::FileCurrupted:
      errorMessage = QString("Поврежденный файл");
      break;
    default:
      errorMessage = QString("Неизвестная ошибка");
  }
  msgBox.setText(errorMessage);
  msgBox.exec();
}

void MainWindow::resetTransformation() {
  fieldWidget->resetTransformation();
  qobject_cast<ControlWidget *>(controlWidget)->setToDefault();
  if (actingWidget) actingWidget->update();
}

void MainWindow::initSettings() {
  if (!settings.contains("initialized") ||
      settings.value("resetSettings").toBool()) {
    settings.clear();
    settings.setValue("initialized", true);
    settings.setValue("resetSettings", false);
    settings.setValue("isOrtho", true);
    settings.setValue("verticesColorRed", 255);
    settings.setValue("verticesColorGreen", 255);
    settings.setValue("verticesColorBlue", 255);
    settings.setValue("backgroundColorRed", 0);
    settings.setValue("backgroundColorGreen", 0);
    settings.setValue("backgroundColorBlue", 0);
    settings.setValue("edgesColorRed", 255);
    settings.setValue("edgesColorGreen", 255);
    settings.setValue("edgesColorBlue", 255);
    settings.setValue("verticesSize", 2);
    settings.setValue("edgesSize", 1);
    settings.setValue("verticesStyle", 1);
    settings.setValue("edgesStyle", 0);
  }
}

void MainWindow::updateFromSettings() {
  initSettings();
  fieldWidget->update();
}

void MainWindow::updateTransformation(TransformationName_e transformation,
                                      float delta) {
  fieldWidget->transformation(transformation, delta);
}

void MainWindow::setNewWidget(QWidget *newWidget) {
  if (actingWidget) {
    actingWidget->deleteLater();
  }
  actingWidget = newWidget;
  actingWidget->show();
  actingWidget->move(MENU_WINDOW_W + 5, mapFromGlobal(QCursor::pos()).y());
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
  if (actingWidget && !actingWidget->rect().contains(
                          actingWidget->mapFromParent(event->pos()))) {
    actingWidget->deleteLater();
    actingWidget = nullptr;
  }
  QWidget::mousePressEvent(event);
}

void MainWindow::createVideo() {
  int width = frames[0].width();
  int height = frames[0].height();

  cv::VideoWriter videoWriter(videoPathFile.toStdString(),
                              cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), FPS,
                              cv::Size(width, height));

  if (!videoWriter.isOpened()) {
    qWarning("Failed to open video writer.");
  } else {
    int totalFrames = frames.size();
    setupProgressBar();
    for (int i = 0; i < totalFrames; ++i) {
      const QImage &frame = frames[i];
      cv::Mat mat(frame.height(), frame.width(), CV_8UC4,
                  const_cast<uchar *>(frame.bits()), frame.bytesPerLine());
      cv::cvtColor(mat, mat, cv::COLOR_RGBA2RGB);

      videoWriter.write(mat);

      int progress =
          static_cast<int>((static_cast<double>(i) / totalFrames) * 100);
      progressBar->setValue(progress);
      QApplication::processEvents();
    }

    videoWriter.release();
    progressBar->deleteLater();
    progressBar = nullptr;
  }
  frames.clear();
}

void MainWindow::setupProgressBar() {
  progressBar = new QProgressBar(this);
  progressBar->setRange(0, 100);
  progressBar->setValue(0);
  progressBar->setStyleSheet(PROGRESS_STYLE);
  progressBar->setGeometry((width() - PROGRESS_W) / 2,
                           (height() - PROGRESS_H) / 2, PROGRESS_W, PROGRESS_H);
  progressBar->show();
}

}  // namespace s21