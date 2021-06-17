#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <reader.h>
//#include <dbproxy.h>
#include <comment.h>
#include <form1.h>
#include <form2.h>
#include <form3.h>

namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_action_triggered();
    void on_action_2_triggered();
    void on_action_3_triggered();

public slots:
    void showMessage(QString);
private:
    Ui::MainWindow *ui;
protected:
    void showEvent(QShowEvent*);
signals:
    void dbanswer(reader);
    void dbanswer(QList<reader>);
    void check();
    void renewTable();
    void find(reader);
    void objectReady(reader);
    void objectReady(comment);
    void reader_model(QSqlRelationalTableModel*);
};




#endif // MAINWINDOW_H
