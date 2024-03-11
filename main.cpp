#include "login_dialog/CLoginDialog.h"
#include "main_window/CMainWindow.h"

#include <QApplication>
#include <QFile>

int main(int argc, char** argv) {
  QApplication app{argc, argv};
  CLoginDialog dlLogin;
  CMainWindow wdMain;

  if (dlLogin.exec() == QDialog::Accepted) {
    wdMain.show();
    return QApplication::exec();
  }
  return 0;
}