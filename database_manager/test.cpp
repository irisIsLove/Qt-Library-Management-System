#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QStringList>
#include <QtDebug>

int main() {
  QCoreApplication::addLibraryPath("./plugins");
  auto db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName("./my_library.db");
  if (db.open()) {
    qDebug() << "111";
  }

  QSqlQuery qeury("select * from READER");
  // if (!qeury.exec()) {
  //   qDebug() << qeury.lastError();
  // }
  while (qeury.next()) {
    qDebug() << qeury.value("NAME").toString();
  }
}