#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QWidget>

namespace Ui {
class CMainWindow;
}

QT_BEGIN_NAMESPACE
class QButtonGroup;
class QSqlTableModel;
QT_END_NAMESPACE

class CMainWindow : public QWidget {
  Q_OBJECT

public:
  explicit CMainWindow(QWidget* parent = nullptr);
  ~CMainWindow();

private slots:
  void slotBtnClicked(int id, bool checked);

private:
  void setIcon();
  void initBtnGroup();
  void initStackedWidget();

  Ui::CMainWindow* ui;
  QButtonGroup* mBtnGroup;
  QSqlTableModel* mBookModel;
  QSqlTableModel* mUserModel;
  QSqlTableModel* mBorrowModel;
};

#endif // CMAINWINDOW_H
