#include "CBorrowWidget.h"
#include "ui_CBorrowWidget.h"

CBorrowWidget::CBorrowWidget(QWidget* parent)
    : QWidget(parent), ui(new Ui::CBorrowWidget) {
  ui->setupUi(this);
}

CBorrowWidget::~CBorrowWidget() { delete ui; }
