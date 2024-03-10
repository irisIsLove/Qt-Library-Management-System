#include "CBookWidget.h"
#include "database_manager/CDataBaseManager.h"
#include "ui_CBookWidget.h"

#include <QMessageBox>
#include <QSqlTableModel>

CBookWidget::CBookWidget(QWidget* parent)
    : QWidget(parent), ui(new Ui::CBookWidget), mBookModel(nullptr) {
  ui->setupUi(this);
}

CBookWidget::~CBookWidget() { delete ui; }

void CBookWidget::setModel(QSqlTableModel* pModel) { mBookModel = pModel; }

void CBookWidget::on_btnAddBook_clicked() {
  int nRow = mBookModel->rowCount();
  mBookModel->insertRow(nRow);

  ui->tbBook->setCurrentIndex(mBookModel->index(nRow, 0));
}

void CBookWidget::on_btnDeleteBook_clicked() {
  int nRow = ui->tbBook->currentIndex().row();
  if (-1 == nRow) {
    QMessageBox::information(this, "", u8"请选中需要删除的行！");
    return;
  }
  mBookModel->removeRow(nRow);
}

void CBookWidget::on_btnSubmitBook_clicked() {
  int ret =
      QMessageBox::warning(this, u8"确认", u8"是否提交修改！", u8"是", u8"否");
  if (0 == ret) {
    mBookModel->submitAll();
  }
}

void CBookWidget::initTable() {
  mBookModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
  {
    mBookModel->setHeaderData(0, Qt::Horizontal, u8"编号");
    mBookModel->setHeaderData(1, Qt::Horizontal, u8"书名");
    mBookModel->setHeaderData(2, Qt::Horizontal, u8"数量");
  }
  mBookModel->select();
  ui->tbBook->setModel(mBookModel);
}

void CBookWidget::on_leSeach_textChanged(const QString& qsSearch) {
  QString qsQuery =
      "book_id LIKE '%" + qsSearch + "%' OR title LIKE '%" + qsSearch + "%'";
  mBookModel->setFilter(qsQuery);
}
