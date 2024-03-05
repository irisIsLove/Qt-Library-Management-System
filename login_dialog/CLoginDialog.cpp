#include "CLoginDialog.h"
#include "ui_CLoginDialog.h"

#include <QIcon>
#include <QLineEdit>
#include <QMessageBox>

CLoginDialog::CLoginDialog(QWidget* parent)
    : QDialog(parent), ui(new Ui::CLoginDialog) {
  ui->setupUi(this);
  ui->lePassword->setEchoMode(QLineEdit::Password);
  setWindowTitle("My Library");
  setWindowIcon(QIcon(":/icon/res/logo.ico"));
}

CLoginDialog::~CLoginDialog() { delete ui; }

void CLoginDialog::on_btnLogin_clicked() { accept(); }

void CLoginDialog::on_btnRegister_clicked() {
  QMessageBox::information(this, "", "注册成功");
}

void CLoginDialog::on_btnFindPassword_clicked() {
  QMessageBox::information(this, "", "找回密码");
}
