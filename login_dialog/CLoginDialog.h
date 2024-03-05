#ifndef CLOGINDIALOG_H
#define CLOGINDIALOG_H

#if defined(_WIN32)
#ifdef LOGIN_DIALOG_EXPORT
#define EXPORT_LOGIN_DIALOG __declspec(dllexport)
#else
#define EXPORT_LOGIN_DIALOG __declspec(dllimport)
#endif
#else
#define EXPORT_LOGIN_DIALOG
#endif

#include <QDialog>

namespace Ui {
class CLoginDialog;
}

class EXPORT_LOGIN_DIALOG CLoginDialog : public QDialog {
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
