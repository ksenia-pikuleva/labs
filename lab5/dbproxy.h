#ifndef DBPROXY_H
#define DBPROXY_H
#include <QObject>
#include <QtSql>
#include "steamer.h"

class DBproxy : public QObject
{
    Q_OBJECT

private:
    QSqlDatabase db;
    static DBproxy* m_instance;
    QSqlTableModel* model;
public:
    DBproxy();
    static DBproxy* getInstance();

signals:
    void dberror(QString);
    void dbanswer(QString);
    void dbanswer(QStringList);
    void dbanswer(QList<steamer>);
    void steamer_model(QSqlTableModel*);
public slots:
    void check();
    void status();
    void save(steamer);
    void find(steamer);
    void renewTable();
};

#endif // DBPROXY_H
