#ifndef CUSERWIDGET_H
#define CUSERWIDGET_H

#include <QWidget>

namespace Ui {
class CUserWidget;
}

QT_BEGIN_NAMESPACE
class QSqlTableModel;
QT_END_NAMESPACE

class CUserWidget : public QWidget {
  Q_OBJECT

public:
  explicit CUserWidget(QWidget* parent = nullptr);
  ~CUserWidget();

private slots:
  void on_btnAddUser_clicked();

  void on_btnDeleteUser_clicked();

  void on_btnSubmitUser_clicked();

  void on_leSeach_textChanged(const QString& qsSearch);

private:
  void initTable();

  Ui::CUserWidget* ui;
  QSqlTableModel* mUserModel;
};

#endif // CUSERWIDGET_H
