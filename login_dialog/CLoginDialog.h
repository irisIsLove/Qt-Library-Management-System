#ifndef CLOGINDIALOG_H
#define CLOGINDIALOG_H

#include <QDialog>

namespace Ui {
class CLoginDialog;
}

class CLoginDialog : public QDialog {
  Q_OBJECT

public:
  explicit CLoginDialog(QWidget* parent = nullptr);
  ~CLoginDialog();

private slots:
  void on_btnLogin_clicked();

  void on_btnRegister_clicked();

  void on_btnFindPassword_clicked();

private:
  Ui::CLoginDialog* ui;
};

#endif // CLOGINDIALOG_H
