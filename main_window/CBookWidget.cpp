#include "CBookWidget.h"
#include "ui_CBookWidget.h"

CBookWidget::CBookWidget(QWidget* parent)
    : QWidget(parent), ui(new Ui::CBookWidget) {
  ui->setupUi(this);
}

CBookWidget::~CBookWidget() { delete ui; }
