#include "s21_menu_widget.h"

namespace s21 {

MenuWidget::MenuWidget(QWidget *parent, QSettings *set)
    : QWidget{parent}, settings(set) {
  setFixedWidth(MENU_WINDOW_W);
  createButtons();
  createPathLine();
  initSignals();
  createLayout();
}

MenuWidget::~MenuWidget() {
  if (buttonOpenModel) buttonOpenModel->deleteLater();
  if (buttonToggleProjection) buttonToggleProjection->deleteLater();
  if (pathLine) pathLine->deleteLater();
  if (buttonScreenshot) buttonScreenshot->deleteLater();
  if (buttonReset) buttonReset->deleteLater();
  if (buttonCaptureVideo) buttonCaptureVideo->deleteLater();
}

void MenuWidget::createButtons() {
  buttonOpenModel = createButton("Open Model");
  buttonReset = createButton("Reset Model");
  buttonToggleProjection = createButton("Toggle Projection");
  buttonScreenshot = createButton("Screenshot");
  buttonCaptureVideo = createButton("Capture Video");

  connect(buttonOpenModel, &QPushButton::clicked, this,
          &MenuWidget::openPressed);
  connect(buttonScreenshot, &QPushButton::clicked, this,
          &MenuWidget::screenshotPressed);
  connect(buttonReset, &QPushButton::clicked, this,
          &MenuWidget::resetTransformationPressed);
  connect(buttonToggleProjection, &QPushButton::clicked, this,
          &MenuWidget::toggleProjectionPressed);
  connect(buttonCaptureVideo, &QPushButton::clicked, this,
          &MenuWidget::captureVideoPressed);
}

QPushButton *MenuWidget::createButton(const QString &text) {
  QPushButton *button = new QPushButton(text, this);
  button->setStyleSheet(BUTTON_STYLE);
  button->setFixedSize(BUTTON_W, BUTTON_H);
  return button;
}

void MenuWidget::createPathLine() {
  pathLine = new QLineEdit(this);
  pathLine->setPlaceholderText("Путь к модели...");
  pathLine->setStyleSheet(LINE_STYLE);
  pathLine->setFixedSize(BUTTON_W, BUTTON_H);
}

void MenuWidget::createLayout() {
  QVBoxLayout *layout = new QVBoxLayout(this);
  layout->addWidget(buttonOpenModel);
  layout->addWidget(pathLine);
  layout->addWidget(buttonReset);
  layout->addWidget(buttonToggleProjection);
  layout->addWidget(buttonScreenshot);
  layout->addWidget(buttonCaptureVideo);
  layout->setSpacing(SPACING);
  layout->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

void MenuWidget::initSignals() {
  MainWindow *mainWindow = qobject_cast<MainWindow *>(parent());
  if (mainWindow) {
    connect(this, &MenuWidget::openNewModel, mainWindow,
            &MainWindow::openModel);
    connect(this, &MenuWidget::resetTransformationPressed, mainWindow,
            &MainWindow::resetTransformation);
    connect(this, &MenuWidget::settingsChanged, mainWindow,
            &MainWindow::updateFromSettings);
    connect(this, &MenuWidget::screenshotSignal, mainWindow,
            &MainWindow::captureScreenshot);
    connect(this, &MenuWidget::captureVideoSignal, mainWindow,
            &MainWindow::captureVideo);
  }
}

void MenuWidget::screenshotPressed() {
  QString directory = QFileDialog::getExistingDirectory(
      this, "Выберите директорию для сохранения", QDir::currentPath(),
      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
  emit screenshotSignal(directory);
}

void MenuWidget::captureVideoPressed() {
  QString directory = QFileDialog::getExistingDirectory(
      this, "Выберите директорию для сохранения", QDir::currentPath(),
      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
  emit captureVideoSignal(directory);
}

void MenuWidget::openPressed() {
  QString pathToFile = pathLine->text();
  pathLine->clear();
  if (pathToFile.isEmpty()) {
    pathToFile = QFileDialog::getOpenFileName(
        this, "Открыть модель", QDir::currentPath(),
        "OBJ Files (*.obj);;All Files (*)");
  }
  openNewModel(pathToFile);
}

void MenuWidget::toggleProjectionPressed() {
  settings->setValue("isOrtho", !(settings->value("isOrtho").toBool()));
  emit settingsChanged();
}

}  // namespace s21