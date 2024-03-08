#include "CUserWidget.h"
#include "const.h"
#include "database_manager/CDataBaseManager.h"
#include "ui_CUserWidget.h"

#include <QMessageBox>
#include <QSqlTableModel>

CUserWidget::CUserWidget(QWidget* parent)
    : QWidget(parent), ui(new Ui::CUserWidget),
      mUserModel(CDataBaseManager::getInstance()->getModel(
          ButtonID::ID_USER_MANAGE, this)) {
  ui->setupUi(this);
  initTable();
}

CUserWidget::~CUserWidget() { delete ui; }

void CUserWidget::initTable() {
  mUserModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
  {
    mUserModel->setHeaderData(0, Qt::Horizontal, u8"姓名");
    mUserModel->setHeaderData(1, Qt::Horizontal, u8"电话号码");
    mUserModel->setHeaderData(2, Qt::Horizontal, u8"地址");
    mUserModel->setHeaderData(3, Qt::Horizontal, u8"年龄");
  }
  ui->tbUser->setModel(mUserModel);
}

void CUserWidget::on_btnAddUser_clicked() {
  int nRow = mUserModel->rowCount();
  mUserModel->insertRow(nRow);

  ui->tbUser->setCurrentIndex(mUserModel->index(nRow, 0));
}

void CUserWidget::on_btnDeleteUser_clicked() {
  int nRow = ui->tbUser->currentIndex().row();
  if (-1 == nRow) {
    QMessageBox::information(this, "", u8"请选中需要删除的行！");
    return;
  }
  mUserModel->removeRow(nRow);
}

void CUserWidget::on_btnSubmitUser_clicked() {
  int ret =
      QMessageBox::warning(this, u8"确认", u8"是否提交修改！", u8"是", u8"否");
  if (QMessageBox::Yes == ret) {
    mUserModel->submitAll();
  }
}

void CUserWidget::on_leSeach_textChanged(const QString& qsSearch) {
  QString qsQuery = "name LIKE '%" + qsSearch + "%';";
  mUserModel->setFilter(qsQuery);
}
