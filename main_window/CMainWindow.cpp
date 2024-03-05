#include "CMainWindow.h"
#include "ui_CMainWindow.h"

#include <QIcon>
#include <qicon.h>

CMainWindow::CMainWindow(QWidget* parent)
    : QWidget(parent), ui(new Ui::CMainWindow) {
  ui->setupUi(this);
  setWindowTitle("My Library");
  setIcon();
}

CMainWindow::~CMainWindow() { delete ui; }

void CMainWindow::setIcon() {
  setWindowIcon(QIcon(":/icon/res/logo.ico"));
  ui->btnBookManage->setIcon(QIcon(":/icon/res/library_management.svg"));
  ui->btnBookBorrow->setIcon(QIcon(":/icon/res/Borrowing_Management.svg"));
  ui->btnBorrowRecord->setIcon(QIcon(":/icon/res/borrowing_record.svg"));
  ui->btnUserManage->setIcon(QIcon(":/icon/res/user_management.svg"));
}