#include "s21_information_widget.h"

namespace s21 {

InformationWidget::InformationWidget(QWidget *parent) : QWidget{parent} {
  initLabels();
  initLayout();
}

InformationWidget::~InformationWidget() {
  if (fileNameText) fileNameText->deleteLater();
  if (fileName) fileName->deleteLater();
  if (verticesText) verticesText->deleteLater();
  if (verticesCount) verticesCount->deleteLater();
  if (edgesText) edgesText->deleteLater();
  if (edgesCount) edgesCount->deleteLater();
}

void InformationWidget::initLabels() {
  fileNameText = createLabel("File name:");
  fileName = createLabel("");
  verticesText = createLabel("Verices count:");
  verticesCount = createLabel("0");
  edgesText = createLabel("Edges count:");
  edgesCount = createLabel("0");
}

QLabel *InformationWidget::createLabel(const QString &text) {
  QLabel *label = new QLabel(text, this);
  label->setFixedHeight(LABEL_H_SIZE);
  label->setStyleSheet(LABEL_STYLE_INFO);
  label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
  return label;
}

void InformationWidget::initLayout() {
  QVBoxLayout *layout = new QVBoxLayout(this);
  QHBoxLayout *layoutName = new QHBoxLayout;
  QHBoxLayout *layoutVertices = new QHBoxLayout;
  QHBoxLayout *layoutEdges = new QHBoxLayout;

  layoutName->addWidget(fileNameText, 1, Qt::AlignLeft | Qt::AlignVCenter);
  layoutName->addWidget(fileName, 1, Qt::AlignRight | Qt::AlignVCenter);

  layoutVertices->addWidget(verticesText, 1, Qt::AlignLeft | Qt::AlignVCenter);
  layoutVertices->addWidget(verticesCount, 1,
                            Qt::AlignRight | Qt::AlignVCenter);

  layoutEdges->addWidget(edgesText, 1, Qt::AlignLeft | Qt::AlignVCenter);
  layoutEdges->addWidget(edgesCount, 1, Qt::AlignRight | Qt::AlignVCenter);

  layout->addLayout(layoutName);
  layout->addLayout(layoutVertices);
  layout->addLayout(layoutEdges);
}

void InformationWidget::updateInformation(QString file, std::size_t vertices,
                                          std::size_t edges) {
  fileName->setText(QFileInfo(file).fileName());
  verticesCount->setText(QString::number(static_cast<qulonglong>(vertices)));
  edgesCount->setText(QString::number(static_cast<qulonglong>(edges)));
  update();
}

}  // namespace s21