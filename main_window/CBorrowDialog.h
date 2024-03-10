#ifndef CBORROWDIALOG_H
#define CBORROWDIALOG_H

#include <QDialog>

namespace Ui {
class CBorrowDialog;
}

class CBorrowDialog : public QDialog {
  Q_OBJECT

public:
  explicit CBorrowDialog(QWidget* parent = nullptr);
  ~CBorrowDialog();

private slots:
  void on_btnOk_clicked();

private:
  Ui::CBorrowDialog* ui;
};

#endif // CBORROWDIALOG_H
