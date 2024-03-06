#include "CRegisterDialog.h"
#include "database_manager/CDataBaseManager.h"
#include "ui_CRegisterDialog.h"

#include <QMessageBox>

CRegisterDialog::CRegisterDialog(E_FIND_OR_REG eMode, QWidget* parent)
    : QDialog(parent), ui(new Ui::CRegisterDialog), mMode(eMode) {
  ui->setupUi(this);

  if (E_FIND_OR_REG::E_FIND == mMode) {
    setWindowTitle(u8"找回密码");
    ui->label->setText(u8"找回密码");
    ui->btnRegiste->setText(u8"确定");
  }
}

CRegisterDialog::~CRegisterDialog() { delete ui; }

bool CRegisterDialog::isPasswordEqual() {
  QString qsPwd = ui->lePassword->text();
  QString qsConfirmPwd = ui->leConfirmPassword->text();

  if (qsPwd.isEmpty() || qsConfirmPwd.isEmpty()) {
    QMessageBox::warning(this, "", u8"密码不能为空！");
  }

  if (qsPwd != qsConfirmPwd) {
    QMessageBox::warning(this, "", u8"密码不一致！");
    return false;
  }

  return true;
}

void CRegisterDialog::on_btnRegiste_clicked() {
  if (E_FIND_OR_REG::E_REGISTE == mMode) {
    registe();
  } else if (E_FIND_OR_REG::E_FIND == mMode) {
    findPwd();
  }
}

void CRegisterDialog::registe() {
  if (!isPasswordEqual()) {
    return;
  }

  QString qsUsername = ui->leUsername->text();
  QString qsPwd = ui->lePassword->text();
  if (CDataBaseManager::getInstance()->findUser(qsUsername)) {
    QMessageBox::information(this, "", u8"用户已存在！");
    return;
  }

  if (!CDataBaseManager::getInstance()->registe(qsUsername, qsPwd)) {
    QMessageBox::information(this, "", u8"注册失败！");
    return;
  } else {
    QMessageBox::information(this, "", u8"注册成功！");
    accept();
  }
}

void CRegisterDialog::findPwd() {
  if (!isPasswordEqual()) {
    return;
  }

  QString qsUsername = ui->leUsername->text();
  QString qsPwd = ui->lePassword->text();
  if (!CDataBaseManager::getInstance()->findUser(qsUsername)) {
    QMessageBox::information(this, "", u8"用户不存在！");
    return;
  }

  if (!CDataBaseManager::getInstance()->modifyPwd(qsUsername, qsPwd)) {
    QMessageBox::information(this, "", u8"修改失败！");
    return;
  } else {
    QMessageBox::information(this, "", u8"修改成功！");
    accept();
  }
}
