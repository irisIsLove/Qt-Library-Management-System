#include "CMainWindow.h"
#include "const.h"
#include "database_manager/CDataBaseManager.h"
#include "main_window/CBookWidget.h"
#include "main_window/CBorrowWidget.h"
#include "main_window/CUserWidget.h"
#include "ui_CMainWindow.h"

#include <QButtonGroup>
#include <QIcon>
#include <QSqlTableModel>

CMainWindow::CMainWindow(QWidget* parent)
    : QWidget(parent), ui(new Ui::CMainWindow),
      mBtnGroup(new QButtonGroup(this)),
      mUserModel(CDataBaseManager::getInstance()->getModel(
          ButtonID::ID_USER_MANAGE, this)),
      mBookModel(CDataBaseManager::getInstance()->getModel(
          ButtonID::ID_BOOK_MANAGE, this)),
      mBorrowModel(CDataBaseManager::getInstance()->getModel(
          ButtonID::ID_BOOK_BORROW, this)) {
  ui->setupUi(this);
  setWindowTitle("My Library");
  setIcon();
  initBtnGroup();
  initStackedWidget();
  connect(mBtnGroup, &QButtonGroup::idToggled, this,
          &CMainWindow::slotBtnClicked);
}

CMainWindow::~CMainWindow() { delete ui; }

void CMainWindow::setIcon() {
  setWindowIcon(QIcon(":/icon/res/logo.ico"));
  ui->btnBookManage->setIcon(QIcon(":/icon/res/library_management.svg"));
  ui->btnBookBorrow->setIcon(QIcon(":/icon/res/Borrowing_Management.svg"));
  ui->btnUserManage->setIcon(QIcon(":/icon/res/user_management.svg"));
}

void CMainWindow::initBtnGroup() {
  mBtnGroup->addButton(ui->btnBookManage,
                       static_cast<int>(ButtonID::ID_BOOK_MANAGE));
  mBtnGroup->addButton(ui->btnBookBorrow,
                       static_cast<int>(ButtonID::ID_BOOK_BORROW));
  mBtnGroup->addButton(ui->btnUserManage,
                       static_cast<int>(ButtonID::ID_USER_MANAGE));
}

void CMainWindow::initStackedWidget() {
  {
    static_cast<CUserWidget*>(
        ui->stackedWidget->widget(static_cast<int>(ButtonID::ID_USER_MANAGE)))
        ->setModel(mUserModel);
    static_cast<CUserWidget*>(
        ui->stackedWidget->widget(static_cast<int>(ButtonID::ID_USER_MANAGE)))
        ->initTable();
  }
  {
    static_cast<CBookWidget*>(
        ui->stackedWidget->widget(static_cast<int>(ButtonID::ID_BOOK_MANAGE)))
        ->setModel(mBookModel);
    static_cast<CBookWidget*>(
        ui->stackedWidget->widget(static_cast<int>(ButtonID::ID_BOOK_MANAGE)))
        ->initTable();
  }
  {
    static_cast<CBorrowWidget*>(
        ui->stackedWidget->widget(static_cast<int>(ButtonID::ID_BOOK_BORROW)))
        ->setModel(mBorrowModel);
    static_cast<CBorrowWidget*>(
        ui->stackedWidget->widget(static_cast<int>(ButtonID::ID_BOOK_BORROW)))
        ->initTable();
  }
}

void CMainWindow::slotBtnClicked(int id, bool checked) {
  if (!checked)
    return;
  ui->stackedWidget->setCurrentIndex(id);
  ButtonID ID = static_cast<ButtonID>(id);
  switch (ID) {
  case ButtonID::ID_USER_MANAGE:
    mUserModel->select();
    break;
  case ButtonID::ID_BOOK_MANAGE:
    mBookModel->select();
    break;
  case ButtonID::ID_BOOK_BORROW:
    mBorrowModel->select();
    break;
  }
}