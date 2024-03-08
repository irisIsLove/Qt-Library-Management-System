#ifndef CREGISTERDIALOG_H
#define CREGISTERDIALOG_H

#include "const.h"

#include <QDialog>

namespace Ui {
class CRegisterDialog;
}

class CRegisterDialog : public QDialog {
  Q_OBJECT

public:
  explicit CRegisterDialog(E_FIND_OR_REG eMode, QWidget* parent = nullptr);
  ~CRegisterDialog();

private slots:
  void on_btnRegiste_clicked();

private:
  bool isPasswordEqual();
  void registe();
  void findPwd();

  E_FIND_OR_REG mMode;
  Ui::CRegisterDialog* ui;
};

#endif // CREGISTERDIALOG_H
