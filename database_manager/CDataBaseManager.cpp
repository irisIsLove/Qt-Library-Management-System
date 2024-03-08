#include "CDataBaseManager.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QtDebug>

CDataBaseManager* CDataBaseManager::instance = nullptr;

CDataBaseManager::CDataBaseManager()
    : mDb(QSqlDatabase::addDatabase("QSQLITE")) {
  mDb.setDatabaseName("my_library.db");
  mDb.open();

  QSqlQuery sqlCreateTable(mDb);
  bool ret = sqlCreateTable.exec(
      "CREATE TABLE IF NOT EXISTS users (username VARCHAR(255) NOT "
      "NULL,password VARCHAR(255) NOT NULL, PRIMARY KEY(username)) ");
  if (!ret) {
    qDebug() << "table user init failed!";
  }

  ret = sqlCreateTable.exec(
      "CREATE TABLE IF NOT EXISTS user_info (name VARCHAR(255) NOT "
      "NULL,phone_number VARCHAR(20) NOT NULL,address TEXT,age INT,PRIMARY KEY "
      "(name, phone_number))");
  if (!ret) {
    qDebug() << "table user_info init failed!";
  }

  ret = sqlCreateTable.exec(
      "CREATE TABLE IF NOT EXISTS books (book_id INT AUTO_INCREMENT PRIMARY "
      "KEY,title VARCHAR(255) NOT NULL,quantity INT NOT NULL)");
  if (!ret) {
    qDebug() << "table books init failed!";
  }

  ret = sqlCreateTable.exec(
      "CREATE TABLE IF NOT EXISTS borrowing_records (record_id INT "
      "AUTO_INCREMENT PRIMARY KEY,user_id INT NOT NULL,book_id INT NOT "
      "NULL,borrow_date DATE NOT NULL,return_date DATE,FOREIGN KEY (user_id) "
      "REFERENCES user_info(user_id),FOREIGN KEY (book_id) REFERENCES "
      "books(book_id))");
  if (!ret) {
    qDebug() << "table borrowing_records init failed!";
  }
}

CDataBaseManager* CDataBaseManager::getInstance() {
  if (nullptr == instance) {
    instance = new CDataBaseManager();
  }
  return instance;
}

bool CDataBaseManager::login(const QString& qsUsername, const QString& qsPwd) {
  QSqlQuery sqlLogin(mDb);
  QString qsSql =
      QString("select * from users where username = '%1' and password = '%2'")
          .arg(qsUsername)
          .arg(qsPwd);
  sqlLogin.exec(qsSql);
  return sqlLogin.next();
}

bool CDataBaseManager::registe(const QString& qsUsername,
                               const QString& qsPwd) {
  QSqlQuery sqlRegiste(mDb);
  QString qsSql =
      QString("insert into users (username, password) values ('%1', '%2');")
          .arg(qsUsername)
          .arg(qsPwd);
  return sqlRegiste.exec(qsSql);
}

bool CDataBaseManager::findUser(const QString& qsUsername) {
  QSqlQuery sqlFind(mDb);
  QString qsSql =
      QString("select * from users where username = '%1'").arg(qsUsername);
  sqlFind.exec(qsSql);
  return sqlFind.next();
}

bool CDataBaseManager::modifyPwd(const QString& qsUsername,
                                 const QString& qsPwd) {
  QSqlQuery sqlModifyPwd(mDb);
  QString qsSql =
      QString("update users set password = '%1' where username = '%2'")
          .arg(qsPwd)
          .arg(qsUsername);
  return sqlModifyPwd.exec(qsSql);
}

QSqlTableModel* CDataBaseManager::getModel(ButtonID id, QObject* parent) {
  QSqlTableModel* pModel = new QSqlTableModel(parent, mDb);

  switch (id) {
  case ButtonID::ID_USER_MANAGE:
    pModel->setTable("user_info");
    break;
  case ButtonID::ID_BOOK_MANAGE:
    pModel->setTable("books");
    break;
  case ButtonID::ID_BOOK_BORROW:
    pModel->setTable("borrowing_records");
    break;
  }

  pModel->select();

  return pModel;
}
