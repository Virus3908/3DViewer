#include "s21_settings_widget.h"

namespace s21 {

SettingsWidget::SettingsWidget(QWidget *parent, QSettings *set,
                               const Settings_e &t, int *x, int *y, int *z)
    : QWidget{parent}, type(t), settings(set), first(x), second(y), third(z) {
  container = new QWidget(this);
  container->setStyleSheet(ACTING_BG_STYLESHEET);
  initSignals();
  initComboBox();
  initSliders();
  initText();
  createLayout();
  container->setFixedSize(this->size());
  container->show();
}

SettingsWidget::~SettingsWidget() {
  if (container) container->deleteLater();
  if (sliderFirst) sliderFirst->deleteLater();
  if (sliderSecond) sliderSecond->deleteLater();
  if (sliderThird) sliderThird->deleteLater();
  if (sliderFourth) sliderFourth->deleteLater();
  if (lineFirst) lineFirst->deleteLater();
  if (lineSecond) lineSecond->deleteLater();
  if (lineThird) lineThird->deleteLater();
  if (lineFourth) lineFourth->deleteLater();
  if (displayColor) displayColor->deleteLater();
  if (comboBox) comboBox->deleteLater();
  if (textFirst) textFirst->deleteLater();
  if (textSecond) textSecond->deleteLater();
  if (textThird) textThird->deleteLater();
  if (textFourth) textFourth->deleteLater();
  if (mainText) mainText->deleteLater();
}

void SettingsWidget::initSignals() {
  MainWindow *mainWindow = qobject_cast<MainWindow *>(parent());
  if (mainWindow) {
    connect(this, &SettingsWidget::settingsChanged, mainWindow,
            &MainWindow::updateFromSettings);
    connect(this, &SettingsWidget::changeTransformation, mainWindow,
            &MainWindow::updateTransformation);
  }
}

void SettingsWidget::initSliders() {
  sliderFirst = createSlider();
  lineFirst = createLine();
  if (type != Settings_e::Scale_e) {
    sliderSecond = createSlider();
    lineSecond = createLine();
    sliderThird = createSlider();
    lineThird = createLine();
    if (type == Settings_e::Vertices_e || type == Settings_e::Edges_e) {
      sliderFourth = createSlider();
      lineFourth = createLine();
    }
  }
  setupSliders();
}

void SettingsWidget::initComboBox() {
  if (type == Settings_e::Vertices_e || type == Settings_e::Edges_e) {
    comboBox = createComboBox();
  }
  setupComboBox();
}

void SettingsWidget::initText() {
  switch (type) {
    case Settings_e::Background_e:
      mainText = createLabel("Background");
      initColorText();
      break;
    case Settings_e::Vertices_e:
      mainText = createLabel("Vertices");
      initColorText();
      break;
    case Settings_e::Edges_e:
      mainText = createLabel("Edges");
      initColorText();
      break;
    case Settings_e::Translate_e:
      mainText = createLabel("Translate");
      initTransformText();
      break;
    case Settings_e::Scale_e:
      mainText = createLabel("Scale");
      textFirst = createLabel("S");
      break;
    case Settings_e::Rotate_e:
      mainText = createLabel("Rotate");
      initTransformText();
      break;
  }
}

void SettingsWidget::initColorText() {
  textFirst = createLabel("R");
  textSecond = createLabel("G");
  textThird = createLabel("B");
  if (type == Settings_e::Vertices_e || type == Settings_e::Edges_e) {
    textFourth = createLabel("S");
  }
  displayColor = new QWidget(this);
  displayColor->setFixedSize(50, 50);  // Задаем размеры прямоугольника
  updateDisplayColor();
}

void SettingsWidget::initTransformText() {
  textFirst = createLabel("X");
  textSecond = createLabel("Y");
  textThird = createLabel("Z");
}

QSlider *SettingsWidget::createSlider() {
  QSlider *slider = new QSlider(Qt::Horizontal, this);
  slider->setFixedSize(SLIDER_W_SIZE, SLIDER_H_SIZE);
  slider->setStyleSheet(SLIDER_STYLE);
  return slider;
}

QLineEdit *SettingsWidget::createLine() {
  QLineEdit *line = new QLineEdit(this);
  line->setFixedSize(LINE_W_SIZE, LINE_H_SIZE);
  line->setStyleSheet(LINE_STYLE);
  return line;
}

QLabel *SettingsWidget::createLabel(const QString &text) {
  QLabel *label = new QLabel(text, this);
  label->setFixedHeight(LABEL_H_SIZE);
  label->setStyleSheet(LABEL_STYLE);
  label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
  return label;
}

QComboBox *SettingsWidget::createComboBox() {
  QComboBox *box = new QComboBox(this);
  box->setFixedHeight(BOX_W_SIZE);
  box->setStyleSheet(COMBOBOX_STYLE);
  return box;
}

void SettingsWidget::createLayout() {
  QHBoxLayout *hLayout = new QHBoxLayout(this);
  QVBoxLayout *vLayout = new QVBoxLayout;
  vLayout->setSpacing(0);
  vLayout->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
  if (mainText) {
    vLayout->addWidget(mainText);
    vLayout->addSpacing(SETTING_SPACING);
  }
  if (comboBox) {
    vLayout->addWidget(comboBox);
    vLayout->addSpacing(SETTING_SPACING);
  }
  if (sliderFirst) {
    vLayout->addLayout(addSliderToLayout(textFirst, sliderFirst, lineFirst));
  }
  if (sliderSecond) {
    vLayout->addLayout(addSliderToLayout(textSecond, sliderSecond, lineSecond));
  }
  if (sliderThird) {
    vLayout->addLayout(addSliderToLayout(textThird, sliderThird, lineThird));
  }
  if (sliderFourth) {
    vLayout->addLayout(addSliderToLayout(textFourth, sliderFourth, lineFourth));
  }
  hLayout->addLayout(vLayout);
  if (displayColor) hLayout->addWidget(displayColor);
  hLayout->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
  adjustSize();
  updateGeometry();
}

QHBoxLayout *SettingsWidget::addSliderToLayout(QLabel *text, QSlider *slider,
                                               QLineEdit *line) {
  QHBoxLayout *layout = new QHBoxLayout;
  layout->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
  layout->addWidget(text);
  layout->addWidget(slider);
  layout->addWidget(line);
  layout->setSpacing(SPACING / 2);
  return layout;
}

void SettingsWidget::setupSliders() {
  switch (type) {
    case Settings_e::Background_e:
      backgroundSlides();
      break;
    case Settings_e::Vertices_e:
      verticesSliders();
      break;
    case Settings_e::Edges_e:
      edgesSliders();
      break;
    case Settings_e::Translate_e:
      translateSlider();
      break;
    case Settings_e::Scale_e:
      scaleSliders();
      break;
    case Settings_e::Rotate_e:
      rotateSliders();
      break;
  }
}

void SettingsWidget::setupComboBox() {
  switch (type) {
    case Settings_e::Vertices_e:
      verticesComboBox();
      break;
    case Settings_e::Edges_e:
      edgesComboBox();
      break;
    case Settings_e::Background_e:
    case Settings_e::Translate_e:
    case Settings_e::Scale_e:
    case Settings_e::Rotate_e:
      break;
  }
}

void SettingsWidget::updateDisplayColor() {
  int red = sliderFirst->value();
  int green = sliderSecond->value();
  int blue = sliderThird->value();

  QString colorStyle = QString("background-color: rgb(%1, %2, %3); %4")
                           .arg(red)
                           .arg(green)
                           .arg(blue)
                           .arg(DISPLAY_COLOR_STYLE);

  displayColor->setStyleSheet(colorStyle);
  displayColor->update();
}

void SettingsWidget::verticesSliders() {
  connectSlider(sliderFirst, lineFirst, "verticesColorRed", 0, 255);
  connectSlider(sliderSecond, lineSecond, "verticesColorGreen", 0, 255);
  connectSlider(sliderThird, lineThird, "verticesColorBlue", 0, 255);
  connectSlider(sliderFourth, lineFourth, "verticesSize", 0, 100);
}

void SettingsWidget::backgroundSlides() {
  connectSlider(sliderFirst, lineFirst, "backgroundColorRed", 0, 255);
  connectSlider(sliderSecond, lineSecond, "backgroundColorGreen", 0, 255);
  connectSlider(sliderThird, lineThird, "backgroundColorBlue", 0, 255);
}

void SettingsWidget::edgesSliders() {
  connectSlider(sliderFirst, lineFirst, "edgesColorRed", 0, 255);
  connectSlider(sliderSecond, lineSecond, "edgesColorGreen", 0, 255);
  connectSlider(sliderThird, lineThird, "edgesColorBlue", 0, 255);
  connectSlider(sliderFourth, lineFourth, "edgesSize", 0, 100);
}
void SettingsWidget::translateSlider() {
  connectSlider(sliderFirst, lineFirst, first, -100, 100, 10,
                TransformationName_e::TranslationX);
  connectSlider(sliderSecond, lineSecond, second, -100, 100, 10,
                TransformationName_e::TranslationY);
  connectSlider(sliderThird, lineThird, third, -100, 100, 10,
                TransformationName_e::TranslationZ);
}
void SettingsWidget::scaleSliders() {
  connectSlider(sliderFirst, lineFirst, first, -100, 100, 100,
                TransformationName_e::Scale);
}

void SettingsWidget::rotateSliders() {
  connectSlider(sliderFirst, lineFirst, first, -360, 360, 1,
                TransformationName_e::RotateX);
  connectSlider(sliderSecond, lineSecond, second, -360, 360, 1,
                TransformationName_e::RotateY);
  connectSlider(sliderThird, lineThird, third, -360, 360, 1,
                TransformationName_e::RotateZ);
}

void SettingsWidget::connectSlider(QSlider *slider, QLineEdit *line,
                                   const QString &key, const int &min,
                                   const int &max) {
  slider->setMinimum(min);
  slider->setMaximum(max);
  slider->setValue(settings->value(key).toInt());
  line->setText(QString::number(settings->value(key).toInt()));

  connect(slider, &QSlider::valueChanged, line, [line, this, key](int value) {
    line->setText(QString::number(value));
    settings->setValue(key, value);
    updateDisplayColor();
    emit settingsChanged();
  });

  connect(line, &QLineEdit::textChanged, slider,
          [slider, this, key](const QString &text) {
            bool ok;
            int value = text.toInt(&ok);
            if (ok) {
              slider->setValue(value);
              settings->setValue(key, value);
              updateDisplayColor();
              emit settingsChanged();
            }
          });
}

void SettingsWidget::connectSlider(QSlider *slider, QLineEdit *line, int *val,
                                   const int &min, const int &max,
                                   const int &modifier,
                                   const TransformationName_e &transformation) {
  slider->setMinimum(min);
  slider->setMaximum(max);
  slider->setValue(*val);
  line->setText(QString::number(*val));

  connect(slider, &QSlider::valueChanged, line,
          [line, this, val, transformation, modifier](int value) {
            line->setText(QString::number(value));
            emit changeTransformation(transformation,
                                      (*val - value) / float(modifier));
            *val = value;
          });

  connect(line, &QLineEdit::textChanged, slider,
          [slider, this, val, transformation, modifier](const QString &text) {
            bool ok;
            int value = text.toInt(&ok);
            if (ok) {
              slider->setValue(value);
              emit changeTransformation(transformation,
                                        (*val - value) / float(modifier));
              *val = value;
            }
          });
}

void SettingsWidget::verticesComboBox() {
  comboBox->addItem("None");
  comboBox->addItem("Rounds");
  comboBox->addItem("Squares");
  connectComboBox(comboBox, "verticesStyle");
}

void SettingsWidget::edgesComboBox() {
  comboBox->addItem("Solid");
  comboBox->addItem("Dashed");
  connectComboBox(comboBox, "edgesStyle");
}

void SettingsWidget::connectComboBox(QComboBox *box, const QString &key) {
  box->setCurrentIndex(settings->value(key).toInt());
  connect(box, &QComboBox::currentIndexChanged, [this, key](int index) {
    settings->setValue(key, index);
    emit settingsChanged();
  });
}

}  // namespace s21