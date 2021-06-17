#ifndef TABWIDGET_H
#define TABWIDGET_H
#include <QTabWidget>
#include <QSqlTableModel>
#include "steamer.h"

namespace Ui {
class TabWidget;
}

class TabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit TabWidget(QWidget *parent = nullptr);
    void resizeTables();
    void showEvent(QShowEvent*);
    void resizeEvent(QResizeEvent *);
    ~TabWidget(); //
public slots:
    void showTables(QStringList);
    void showData(QList<steamer>);

private slots:
    void setModel(QSqlTableModel*);
    void showMessage(QString);
    void on_pushButton_clicked();
    void on_TabWidget_currentChanged(int index);
    void on_lineEdit_7_returnPressed();

signals:
    void check();
    void renewTable();
    void find(steamer);
    void objectReady(steamer);
private:
    Ui::TabWidget *ui;
};
#endif // TABWIDGET_H
