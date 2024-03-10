#ifndef CBOOKWIDGET_H
#define CBOOKWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QSqlTableModel;
QT_END_NAMESPACE

namespace Ui {
class CBookWidget;
}

class CBookWidget : public QWidget {
  Q_OBJECT

public:
  explicit CBookWidget(QWidget* parent = nullptr);
  ~CBookWidget();

  void setModel(QSqlTableModel* pModel);

  void initTable();

private slots:
  void on_btnAddBook_clicked();

  void on_btnDeleteBook_clicked();

  void on_btnSubmitBook_clicked();

  void on_leSeach_textChanged(const QString& qsSearch);

private:
  Ui::CBookWidget* ui;
  QSqlTableModel* mBookModel;
};

#endif // CBOOKWIDGET_H
