#include "CMainWindow.h"
#include "ui_CMainWindow.h"

#include <QButtonGroup>
#include <QIcon>
#include <QtDebug>

enum class ButtonID : int {
  ID_USER_MANAGE,
  ID_BOOK_MANAGE,
  ID_BOOK_BORROW,
  ID_BORROW_RECORD,
};

CMainWindow::CMainWindow(QWidget* parent)
    : QWidget(parent), ui(new Ui::CMainWindow),
      mBtnGroup(new QButtonGroup(this)) {
  ui->setupUi(this);
  setWindowTitle("My Library");
  setIcon();
  initBtnGroup();
  connect(mBtnGroup, &QButtonGroup::idToggled, this,
          &CMainWindow::slotBtnClicked);
}

CMainWindow::~CMainWindow() { delete ui; }

void CMainWindow::setIcon() {
  setWindowIcon(QIcon(":/icon/res/logo.ico"));
  ui->btnBookManage->setIcon(QIcon(":/icon/res/library_management.svg"));
  ui->btnBookBorrow->setIcon(QIcon(":/icon/res/Borrowing_Management.svg"));
  ui->btnBorrowRecord->setIcon(QIcon(":/icon/res/borrowing_record.svg"));
  ui->btnUserManage->setIcon(QIcon(":/icon/res/user_management.svg"));
}

void CMainWindow::initBtnGroup() {
  mBtnGroup->addButton(ui->btnBookManage,
                       static_cast<int>(ButtonID::ID_BOOK_MANAGE));
  mBtnGroup->addButton(ui->btnBookBorrow,
                       static_cast<int>(ButtonID::ID_BOOK_BORROW));
  mBtnGroup->addButton(ui->btnBorrowRecord,
                       static_cast<int>(ButtonID::ID_BORROW_RECORD));
  mBtnGroup->addButton(ui->btnUserManage,
                       static_cast<int>(ButtonID::ID_USER_MANAGE));
}

void CMainWindow::slotBtnClicked(int id, bool checked) {
  if (!checked)
    return;

  auto btnID = static_cast<ButtonID>(id);
  switch (btnID) {
  case ButtonID::ID_USER_MANAGE:
  case ButtonID::ID_BOOK_MANAGE:
  case ButtonID::ID_BOOK_BORROW:
  case ButtonID::ID_BORROW_RECORD:
    break;
  }
}
