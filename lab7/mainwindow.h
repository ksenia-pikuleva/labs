#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include "counter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QAction *run, *add, *list, *jrn; // атрибуты-указатели для панели инструментов
signals:
    void start();
    void stop();
    void newCounter(counter);
    void answer(QString);  // уведомления о событиях окна
    void acqlog();   // сигнал диспетчеру для подготовки журнала
    void acqlist();  // сигнал диспетчеру для подготовки списка счетчиков
    void acqprefs();
    void finish();
protected:
    void showEvent(QShowEvent* event);
    void closeEvent(QCloseEvent * event);
private slots:
    void runProcess();        // смена иконок при старт\стоп
    void addCounter();        // слот для появления диалога по добавлению счетчика
    void showStatus(QString); // отображение статуса в статусной строке
    void showData(QString);   // отображение списка счетчиков или журнала действий


};
#endif // MAINWINDOW_H
