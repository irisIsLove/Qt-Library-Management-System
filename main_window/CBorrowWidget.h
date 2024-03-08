#ifndef CBORROWWIDGET_H
#define CBORROWWIDGET_H

#include <QWidget>

namespace Ui {
class CBorrowWidget;
}

class CBorrowWidget : public QWidget {
  Q_OBJECT

public:
  explicit CBorrowWidget(QWidget* parent = nullptr);
  ~CBorrowWidget();

private:
  Ui::CBorrowWidget* ui;
};

#endif // CBORROWWIDGET_H
