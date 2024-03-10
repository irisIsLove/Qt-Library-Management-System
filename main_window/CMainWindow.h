#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#if defined(_WIN32)
#ifdef MAIN_WINDOW_EXPORT
#define EXPORT_MAIN_WINDOW __declspec(dllexport)
#else
#define EXPORT_MAIN_WINDOW __declspec(dllimport)
#endif
#else
#define EXPORT_MAIN_WINDOW
#endif

#include <QWidget>

namespace Ui {
class CMainWindow;
}

QT_BEGIN_NAMESPACE
class QButtonGroup;
class QSqlTableModel;
QT_END_NAMESPACE

class EXPORT_MAIN_WINDOW CMainWindow : public QWidget {
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
