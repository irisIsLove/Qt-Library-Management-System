#ifndef CDATABASEMANAGER_H
#define CDATABASEMANAGER_H

#if defined(_WIN32)
#ifdef DATABASE_MANAGER_EXPORT
#define EXPORT_DATABASE_MANAGER __declspec(dllexport)
#else
#define EXPORT_DATABASE_MANAGER __declspec(dllimport)
#endif
#else
#define EXPORT_DATABASE_MANAGER
#endif

#include <QSqlDatabase>

class CDataBaseManager {
public:
  static CDataBaseManager* getInstance();
  bool login(const QString& qsUsername, const QString& qsPwd);
  bool registe(const QString& qsUsername, const QString& qsPwd);
  bool findUser(const QString& qsUsername);
  bool modifyPwd(const QString& qsUsername, const QString& qsPwd);

private:
  CDataBaseManager();
  ~CDataBaseManager();
  CDataBaseManager(const CDataBaseManager&) = delete;
  CDataBaseManager& operator=(const CDataBaseManager&) = delete;
  CDataBaseManager(CDataBaseManager&&) = delete;
  CDataBaseManager& operator=(CDataBaseManager&&) = delete;

  QSqlDatabase mDb;
  static CDataBaseManager* instance;
};

#endif // CDATABASEMANAGER_H
