#include "CDataBaseManager.h"

#include <QDate>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRelationalTableModel>
#include <QSqlTableModel>

CDataBaseManager* CDataBaseManager::instance = nullptr;

CDataBaseManager::CDataBaseManager()
    : mDb(QSqlDatabase::addDatabase("QSQLITE")) {
  mDb.setDatabaseName("my_library.db");
  mDb.open();

  QSqlQuery sqlCreateTable(mDb);
  bool ret = sqlCreateTable.exec(
      "CREATE TABLE IF NOT EXISTS users (username VARCHAR(255) NOT "
      "NULL,password VARCHAR(255) NOT NULL, PRIMARY KEY(username)) ");

  ret = sqlCreateTable.exec(
      "CREATE TABLE IF NOT EXISTS user_info (user_id INTEGER NOT NULL PRIMARY "
      "KEY AUTOINCREMENT, name VARCHAR(225) NOT NULL, phone_number "
      "VARCHAR(255) NOT NULL UNIQUE, age INT NOT NULL, address VARCHAR(225) "
      "NOT NULL)");

  ret = sqlCreateTable.exec(
      "CREATE TABLE IF NOT EXISTS books (book_id INT AUTO_INCREMENT PRIMARY "
      "KEY,title VARCHAR(255) NOT NULL,quantity INT NOT NULL)");

  ret = sqlCreateTable.exec(
      "CREATE TABLE IF NOT EXISTS borrow_record (record_id VARCHAR(255) NOT "
      "NULL PRIMARY KEY, user_id INTEGER NOT NULL, book_id INT "
      "NOT NULL, borrow_date DATE NOT NULL, return_date DATE, Foreign Key "
      "(user_id) REFERENCES user_info (user_id), Foreign Key (book_id) "
      "REFERENCES books (book_id))");
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

void CDataBaseManager::borrowBook(const QString& qsUserId,
                                  const QString& qsBookId, QString& qsErr) {
  QSqlQuery sqlBorrowBook(mDb);
  QString qsSql =
      QString("select * from user_info where user_id = '%1'").arg(qsUserId);
  sqlBorrowBook.exec(qsSql);
  if (!sqlBorrowBook.next()) {
    qsErr = u8"未查到此用户id！";
    return;
  }

  qsSql = QString("select * from books where book_id = '%1'").arg(qsBookId);
  sqlBorrowBook.exec(qsSql);
  if (!sqlBorrowBook.next()) {
    qsErr = u8"未查到此书籍编号！";
    return;
  }
  if (sqlBorrowBook.value("quantity").toInt() == 0) {
    qsErr = u8"书籍数量不足！";
    return;
  }

  QString qsRecordId =
      QString("%1_%2_%3")
          .arg(qsUserId)
          .arg(qsBookId)
          .arg(QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));

  qsSql =
      QString(
          "INSERT INTO borrow_record(borrow_date,user_id,book_id,record_id) "
          "VALUES('%1',%2,%3,'%4')")
          .arg(QDate::currentDate().toString("yyyy-MM-dd"))
          .arg(qsUserId)
          .arg(qsBookId)
          .arg(qsRecordId);
  if (!sqlBorrowBook.exec(qsSql)) {
    qsErr = sqlBorrowBook.lastError().text();
    return;
  }

  qsSql = QString("update books set quantity = quantity - 1 where book_id = %1")
              .arg(qsBookId);
  if (!sqlBorrowBook.exec(qsSql)) {
    qsErr = sqlBorrowBook.lastError().text();
    return;
  }
}

void CDataBaseManager::returnBook(const QString& qsRecordId, QString& qsErr) {
  QSqlQuery sqlReturnBook(mDb);

  QStringList qsList = qsRecordId.split('_');

  QString qsSql = QString("update borrow_record set return_date = '%1' where "
                          "user_id = %2 and book_id = %3")
                      .arg(QDate::currentDate().toString("yyyy-MM-dd"))
                      .arg(qsList[0])
                      .arg(qsList[1]);
  if (!sqlReturnBook.exec(qsSql)) {
    qsErr = sqlReturnBook.lastError().text();
    return;
  }

  qsSql = QString("update books set quantity = quantity + 1 where book_id = %1")
              .arg(qsList[1]);
  if (!sqlReturnBook.exec(qsSql)) {
    qsErr = sqlReturnBook.lastError().text();
    return;
  }
}

QSqlTableModel* CDataBaseManager::getModel(ButtonID id, QObject* parent) {
  QSqlTableModel* pModel = nullptr;

  switch (id) {
  case ButtonID::ID_USER_MANAGE:
    pModel = new QSqlTableModel(parent, mDb);
    pModel->setTable("user_info");
    break;
  case ButtonID::ID_BOOK_MANAGE:
    pModel = new QSqlTableModel(parent, mDb);
    pModel->setTable("books");
    break;
  case ButtonID::ID_BOOK_BORROW:
    pModel = new QSqlRelationalTableModel(parent, mDb);
    pModel->setTable("borrow_record");
    break;
  }

  return pModel;
}
