#include "s21_control_widget.h"

namespace s21 {

ControlWidget::ControlWidget(QWidget *parent, QSettings *set)
    : QWidget{parent}, settings(set) {
  createButtons();
  createLayout();
  setToDefault();
  initSignals();
}

ControlWidget::~ControlWidget() {
  if (backgroundSettingsButton) backgroundSettingsButton->deleteLater();
  if (verticesSettingsButton) verticesSettingsButton->deleteLater();
  if (edgesSettingsButton) edgesSettingsButton->deleteLater();
  if (translateButton) translateButton->deleteLater();
  if (scaleButton) scaleButton->deleteLater();
  if (rotateButton) rotateButton->deleteLater();
}

void ControlWidget::createButtons() {
  backgroundSettingsButton = createButton("Background settings");
  verticesSettingsButton = createButton("Vertices settings");
  edgesSettingsButton = createButton("Edges settings");
  translateButton = createButton("Translate");
  scaleButton = createButton("Scale");
  rotateButton = createButton("Roate");

  connect(backgroundSettingsButton, &QPushButton::clicked, this,
          &ControlWidget::backgroundSettingsPressed);
  connect(verticesSettingsButton, &QPushButton::clicked, this,
          &ControlWidget::verticesSettingsPressed);
  connect(edgesSettingsButton, &QPushButton::clicked, this,
          &ControlWidget::edgesSettingsPressed);
  connect(translateButton, &QPushButton::clicked, this,
          &ControlWidget::translatePressed);
  connect(scaleButton, &QPushButton::clicked, this,
          &ControlWidget::scalePressed);
  connect(rotateButton, &QPushButton::clicked, this,
          &ControlWidget::rotatePressed);
}

QPushButton *ControlWidget::createButton(const QString &text) {
  QPushButton *button = new QPushButton(text, this);
  button->setStyleSheet(BUTTON_STYLE);
  button->setFixedSize(BUTTON_W, BUTTON_H);
  return button;
}

void ControlWidget::createLayout() {
  QVBoxLayout *layout = new QVBoxLayout(this);
  layout->addWidget(backgroundSettingsButton);
  layout->addWidget(verticesSettingsButton);
  layout->addWidget(edgesSettingsButton);
  layout->addWidget(translateButton);
  layout->addWidget(scaleButton);
  layout->addWidget(rotateButton);
  layout->setSpacing(SPACING);
  layout->setContentsMargins(0, 0, 0, 0);
  layout->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

void ControlWidget::initSignals() {
  MainWindow *mainWindow = qobject_cast<MainWindow *>(parent());
  if (mainWindow) {
    connect(this, &ControlWidget::switchToNewWidget, mainWindow,
            &MainWindow::setNewWidget);
    connect(this, &ControlWidget::settingsChanged, mainWindow,
            &MainWindow::updateFromSettings);
  }
}

void ControlWidget::setToDefault() {
  translateX = 0;
  translateY = 0;
  translateZ = 0;
  scale = 0;
  rotateX = 0;
  rotateY = 0;
  rotateZ = 0;
}

void ControlWidget::backgroundSettingsPressed() {
  QWidget *newWidget =
      new SettingsWidget(qobject_cast<QWidget *>(this->parent()->parent()),
                         settings, Settings_e::Background_e);
  switchToNewWidget(newWidget);
}

void ControlWidget::verticesSettingsPressed() {
  QWidget *newWidget =
      new SettingsWidget(qobject_cast<QWidget *>(this->parent()->parent()),
                         settings, Settings_e::Vertices_e);
  switchToNewWidget(newWidget);
}

void ControlWidget::edgesSettingsPressed() {
  QWidget *newWidget =
      new SettingsWidget(qobject_cast<QWidget *>(this->parent()->parent()),
                         settings, Settings_e::Edges_e);
  switchToNewWidget(newWidget);
}

void ControlWidget::translatePressed() {
  QWidget *newWidget = new SettingsWidget(
      qobject_cast<QWidget *>(this->parent()->parent()), settings,
      Settings_e::Translate_e, &translateX, &translateY, &translateZ);
  switchToNewWidget(newWidget);
}

void ControlWidget::scalePressed() {
  QWidget *newWidget =
      new SettingsWidget(qobject_cast<QWidget *>(this->parent()->parent()),
                         settings, Settings_e::Scale_e, &scale);
  switchToNewWidget(newWidget);
}

void ControlWidget::rotatePressed() {
  QWidget *newWidget = new SettingsWidget(
      qobject_cast<QWidget *>(this->parent()->parent()), settings,
      Settings_e::Rotate_e, &rotateX, &rotateY, &rotateZ);
  switchToNewWidget(newWidget);
}

}  // namespace s21