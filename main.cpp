#include "login_dialog/CLoginDialog.h"
#include "main_window/CMainWindow.h"

#include <QApplication>
#include <QFile>

int main(int argc, char** argv) {
  QApplication app{argc, argv};
  CLoginDialog dlLogin;
  CMainWindow wdMain;

  QFile qssLogin(":/qss/style/login_dialog.qss");
  if (qssLogin.open(QFile::ReadOnly)) {
    dlLogin.setStyleSheet(qssLogin.readAll());
  }

  QFile qssMain(":/qss/style/main_window.qss");
  if (qssMain.open(QFile::ReadOnly)) {
    wdMain.setStyleSheet(qssMain.readAll());
  }

  if (dlLogin.exec() == QDialog::Accepted) {
    wdMain.show();
    return app.exec();
  }
  return 0;
}