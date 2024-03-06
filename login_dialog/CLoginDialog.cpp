#include "CLoginDialog.h"
#include "database_manager/CDataBaseManager.h"
#include "login_dialog/CRegisterDialog.h"
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

void CLoginDialog::on_btnLogin_clicked() {
  QString qsUsername = ui->leUsername->text();
  QString qsPwd = ui->lePassword->text();

  if (CDataBaseManager::getInstance()->login(qsUsername, qsPwd)) {
    accept();
  } else {
    QMessageBox::information(this, "", u8"密码错误！");
  }
}

void CLoginDialog::on_btnRegister_clicked() {
  CRegisterDialog d(E_FIND_OR_REG::E_REGISTE, this);
  d.exec();
}

void CLoginDialog::on_btnFindPassword_clicked() {
  CRegisterDialog d(E_FIND_OR_REG::E_FIND, this);
  d.exec();
}
