#ifndef CBORROWWIDGET_H
#define CBORROWWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QSqlRelationalTableModel;
class QSqlTableModel;
QT_END_NAMESPACE

namespace Ui {
class CBorrowWidget;
}

class CBorrowWidget : public QWidget {
  Q_OBJECT

public:
  explicit CBorrowWidget(QWidget* parent = nullptr);
  ~CBorrowWidget();

  void setModel(QSqlTableModel* pModel);

  void initTable();

private slots:
  void on_btnBorrowBook_clicked();

  void on_btnReturnBook_clicked();

  void on_leSeach_textChanged(const QString& arg1);

private:
  Ui::CBorrowWidget* ui;
  QSqlRelationalTableModel* mRecordModel;
};

#endif // CBORROWWIDGET_H
