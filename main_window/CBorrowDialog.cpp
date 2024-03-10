#include "CBorrowDialog.h"
#include "database_manager/CDataBaseManager.h"
#include "ui_CBorrowDialog.h"

#include <QMessageBox>

CBorrowDialog::CBorrowDialog(QWidget* parent)
    : QDialog(parent), ui(new Ui::CBorrowDialog) {
  ui->setupUi(this);
}

CBorrowDialog::~CBorrowDialog() { delete ui; }

void CBorrowDialog::on_btnOk_clicked() {
  QString qsUserId = ui->leUserId->text();
  QString qsBookId = ui->leBookId->text();

  if (qsUserId.isEmpty() || qsBookId.isEmpty()) {
    QMessageBox::warning(this, "", u8"借阅信息不能为空！");
    return;
  }

  QString qsErr = "";
  CDataBaseManager::getInstance()->borrowBook(qsUserId, qsBookId, qsErr);
  if (!qsErr.isEmpty()) {
    QMessageBox::warning(this, "", qsErr);
    return;
  }

  close();
}
