#ifndef CBOOKWIDGET_H
#define CBOOKWIDGET_H

#include <QWidget>

namespace Ui {
class CBookWidget;
}

class CBookWidget : public QWidget {
  Q_OBJECT

public:
  explicit CBookWidget(QWidget* parent = nullptr);
  ~CBookWidget();

private:
  Ui::CBookWidget* ui;
};

#endif // CBOOKWIDGET_H
