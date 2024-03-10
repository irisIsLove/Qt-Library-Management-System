#include "CBorrowWidget.h"
#include "CBorrowDialog.h"
#include "database_manager/CDataBaseManager.h"
#include "ui_CBorrowWidget.h"

#include <QDate>
#include <QMessageBox>
#include <QSqlRelationalTableModel>

CBorrowWidget::CBorrowWidget(QWidget* parent)
    : QWidget(parent), ui(new Ui::CBorrowWidget), mRecordModel(nullptr) {
  ui->setupUi(this);
}

CBorrowWidget::~CBorrowWidget() { delete ui; }

void CBorrowWidget::setModel(QSqlTableModel* pModel) {
  mRecordModel = static_cast<QSqlRelationalTableModel*>(pModel);
}

void CBorrowWidget::initTable() {
  ui->tbBorrow->setEditTriggers(QAbstractItemView::NoEditTriggers);
  ui->tbBorrow->setModel(mRecordModel);
  mRecordModel->setRelation(2, QSqlRelation("books", "book_id", "title"));
  mRecordModel->setRelation(1, QSqlRelation("user_info", "user_id", "name"));
  mRecordModel->select();
  {
    mRecordModel->setHeaderData(0, Qt::Horizontal, u8"记录id");
    mRecordModel->setHeaderData(1, Qt::Horizontal, u8"用户");
    mRecordModel->setHeaderData(2, Qt::Horizontal, u8"书名");
    mRecordModel->setHeaderData(3, Qt::Horizontal, u8"借取日期");
    mRecordModel->setHeaderData(4, Qt::Horizontal, u8"归还日期");
    // mRecordModel->moveRow(const QModelIndex &sourceParent, int sourceRow,
    // const QModelIndex &destinationParent, int destinationChild)
  }
}

void CBorrowWidget::on_btnBorrowBook_clicked() {
  CBorrowDialog d(this);
  d.exec();
  mRecordModel->select();
}

void CBorrowWidget::on_btnReturnBook_clicked() {
  int nRow = ui->tbBorrow->currentIndex().row();
  if (-1 == nRow) {
    QMessageBox::information(this, "", u8"请选中需要归还的记录！");
    return;
  }

  QString qsRecordId = mRecordModel
                           ->data(mRecordModel->index(
                               nRow, mRecordModel->fieldIndex("record_id")))
                           .toString();

  QString qsReturnDate = mRecordModel
                             ->data(mRecordModel->index(
                                 nRow, mRecordModel->fieldIndex("return_date")))
                             .toString();
  if (!qsReturnDate.isEmpty()) {
    QMessageBox::warning(this, "", u8"请勿重复归还图书！");
    return;
  }

  QString qsErr = "";
  CDataBaseManager::getInstance()->returnBook(qsRecordId, qsErr);
  if (!qsErr.isEmpty()) {
    QMessageBox::warning(this, "", qsErr);
  } else {
    QMessageBox::information(this, "", u8"归还成功！");
  }
  mRecordModel->select();
}

void CBorrowWidget::on_leSeach_textChanged(const QString& qsSearch) {
  QString qsFilter = "name LIKE '%" + qsSearch + "%' OR title LIKE '%" +
                     qsSearch + "%' OR record_id LIKE '%" + qsSearch + "%'";
  mRecordModel->setFilter(qsFilter);
}
