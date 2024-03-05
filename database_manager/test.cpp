#include "CDataBaseManager.h"

#include <QCoreApplication>
#include <QtDebug>

int main() {
  QCoreApplication::addLibraryPath("./plugins");

  qDebug() << "Login status: "
           << CDataBaseManager::getInstance()->login("Iris", "123456");
}