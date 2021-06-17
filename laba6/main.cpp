#include "mainwindow.h"
#include <QApplication>
#include "dbproxy.h"
int main(int argc, char *argv[])
{
        QApplication a(argc, argv);
        MainWindow w;
        QObject::connect(DBproxy::getInstance(), SIGNAL(dbanswer(QList<reader>)), &w, SIGNAL(dbanswer(QList<reader>)));
        QObject::connect(&w, SIGNAL(check()), DBproxy::getInstance(), SLOT(check()));
        QObject::connect(&w, SIGNAL(find(reader)), DBproxy::getInstance(), SLOT(find(reader)));
        QObject::connect(&w, SIGNAL(objectReady(reader)), DBproxy::getInstance(), SLOT(save(reader)));
        QObject::connect(DBproxy::getInstance(), SIGNAL(dbanswer(QString)), &w, SLOT(showMessage(QString)));
        QObject::connect(DBproxy::getInstance(), SIGNAL(dberror(QString)), &w, SLOT(showMessage(QString)));
        QObject::connect(DBproxy::getInstance(), SIGNAL(dbanswer(reader)), &w, SIGNAL(dbanswer(reader)));
        QObject::connect(&w, SIGNAL(renewTable()), DBproxy::getInstance(), SLOT(renewTable()));
        QObject::connect(&w, SIGNAL(objectReady(comment)), DBproxy::getInstance(), SLOT(save(comment)));
        QObject::connect(DBproxy::getInstance(), SIGNAL(reader_model(QSqlRelationalTableModel*)), &w, SIGNAL(reader_model(QSqlRelationalTableModel*)));

        w.show();
        return a.exec();

}
