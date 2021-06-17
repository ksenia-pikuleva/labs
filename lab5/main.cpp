#include "dbproxy.h"
#include "tabwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TabWidget w;
    QObject::connect(DBproxy::getInstance(), SIGNAL(dberror(QString)), &w, SLOT(showMessage(QString)));
    QObject::connect(DBproxy::getInstance(), SIGNAL(dbanswer(QString)), &w, SLOT(showMessage(QString)));
    QObject::connect(DBproxy::getInstance(), SIGNAL(dbanswer(QStringList)), &w, SLOT(showTables(QStringList)));
    QObject::connect(DBproxy::getInstance(), SIGNAL(dbanswer(QList<steamer>)), &w, SLOT(showData(QList<steamer>)));
    QObject::connect(DBproxy::getInstance(), SIGNAL(steamer_model(QSqlTableModel*)), &w, SLOT(setModel(QSqlTableModel*)));
    QObject::connect(&w, SIGNAL(check()), DBproxy::getInstance(), SLOT(check()));
    QObject::connect(&w, SIGNAL(check()), DBproxy::getInstance(), SLOT(status()));
    QObject::connect(&w, SIGNAL(renewTable()), DBproxy::getInstance(), SLOT(renewTable()));
    QObject::connect(&w, SIGNAL(find(steamer)), DBproxy::getInstance(), SLOT(find(steamer)));
    QObject::connect(&w, SIGNAL(objectReady(steamer)), DBproxy::getInstance(), SLOT(save(steamer)));
    w.show();
    return a.exec();
}
