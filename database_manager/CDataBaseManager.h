#ifndef CDATABASEMANAGER_H
#define CDATABASEMANAGER_H

#include "const.h"

#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
class QObject;
class QSqlTableModel;
QT_END_NAMESPACE

class CDataBaseManager {
public:
  CDataBaseManager(const CDataBaseManager&) = delete;
  CDataBaseManager& operator=(const CDataBaseManager&) = delete;
  CDataBaseManager(CDataBaseManager&&) = delete;
  CDataBaseManager& operator=(CDataBaseManager&&) = delete;
  static CDataBaseManager* getInstance();
  bool login(const QString& qsUsername, const QString& qsPwd);
  bool registe(const QString& qsUsername, const QString& qsPwd);
  bool findUser(const QString& qsUsername);
  bool modifyPwd(const QString& qsUsername, const QString& qsPwd);

  void borrowBook(const QString& qsUserId, const QString& qsBookId,
                  QString& qsErr);
  void returnBook(const QString& qsRecordId, QString& qsErr);

  QSqlTableModel* getModel(ButtonID id, QObject* parent);

private:
  CDataBaseManager();
  ~CDataBaseManager();

  QSqlDatabase mDb;
  static CDataBaseManager* instance;
};

#endif // CDATABASEMANAGER_H
