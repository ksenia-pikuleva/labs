#ifndef DBPROXY_H
#define DBPROXY_H
#include <QObject>
#include <QtSql>
#include "reader.h"
#include <comment.h>
class DBproxy : public QObject
{
    Q_OBJECT
private:
    QSqlDatabase db;
    static DBproxy* m_instance;
    QSqlRelationalTableModel* model;
public:
    DBproxy();
    static DBproxy* getInstance();
signals:
    void dberror(QString);
    void dbanswer(QString);
    void dbanswer(QStringList);
    void dbanswer(reader);
    void dbanswer(QList<reader>);
    void reader_model(QSqlRelationalTableModel*);
public slots:
    void status();
    void check();
    void save(reader);
    void save (comment);
    void find(reader);
    void renewTable();
};

#endif // DBPROXY_H
