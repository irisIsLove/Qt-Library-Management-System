#include "CUserWidget.h"
#include "database_manager/CDataBaseManager.h"
#include "ui_CUserWidget.h"

#include <QMessageBox>
#include <QSqlTableModel>

CUserWidget::CUserWidget(QWidget* parent)
    : QWidget(parent), ui(new Ui::CUserWidget), mUserModel(nullptr) {
  ui->setupUi(this);
}

CUserWidget::~CUserWidget() { delete ui; }

void CUserWidget::setModel(QSqlTableModel* pModel) { mUserModel = pModel; }

void CUserWidget::initTable() {
  mUserModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
  ui->tbUser->setModel(mUserModel);
  mUserModel->select();
  {
    mUserModel->setHeaderData(0, Qt::Horizontal, u8"用户id");
    mUserModel->setHeaderData(1, Qt::Horizontal, u8"姓名");
    mUserModel->setHeaderData(2, Qt::Horizontal, u8"电话号码");
    mUserModel->setHeaderData(3, Qt::Horizontal, u8"年龄");
    mUserModel->setHeaderData(4, Qt::Horizontal, u8"地址");
  }
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
  if (0 == ret) {
    mUserModel->submitAll();
  }
}

void CUserWidget::on_leSeach_textChanged(const QString& qsSearch) {
  QString qsQuery = "name LIKE '%" + qsSearch + "%' OR phone_number LIKE '%" +
                    qsSearch + "%' OR user_id LIKE '%" + qsSearch + "%'";
  mUserModel->setFilter(qsQuery);
}
