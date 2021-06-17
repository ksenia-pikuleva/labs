#include "dbproxy.h"
#include <QtDebug>
#include <QString>

DBproxy* DBproxy::m_instance=nullptr;

DBproxy::DBproxy() : QObject(0)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QDir::homePath() + "/database1.db");
    model = new QSqlTableModel(this);
}

DBproxy* DBproxy::getInstance()
{
    if (m_instance == 0) m_instance = new DBproxy;
    return m_instance;
}

void DBproxy::check()
{
    if (!db.open()) emit dberror (db.lastError().text());
    else
    {
        QString qstr = "create table if not exists `steamer`"
        "(`id` INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
        "`Название` VARCHAR(30), Компания VARCHAR(30), Места VARCHAR(10),"
        "Фамилия VARCHAR(30), Имя VARCHAR(30), Отчество VARCHAR(30));";
        QSqlQuery query(db);
        if (query.exec(qstr))
            emit dbanswer("Таблица `steamer` создана или уже существует!");
        else emit dberror(query.lastError().text());

        model->setTable("steamer");
        model->setSort(1, Qt::AscendingOrder);
    }    
}

void DBproxy::status()
{
    emit dbanswer (db.tables());
}

void DBproxy::save(steamer arg)

{
    QString as, qIns, qUpd;
    qIns = "insert into `steamer` (Название, Компания, Места, "
            "Фамилия, Имя, Отчество) values ('%1', '%2', '%3', '%4', '%5', '%6')";
    qUpd = "update steamer set id='%1', Название='%2', sCompany='%3', "
            "sPlaces='%4', cFam='%5', cName='%6', cPatr='%7'"
            "where id='%1';";
    if (db.isOpen())
    {
        if (arg.id()=="0")

             as=qIns.arg(arg.sName()).arg(arg.sCompany()).arg(arg.sPlaces()).arg(arg.cFam()).arg(arg.cName()).arg(arg.cPatr());

        else as=qUpd.arg(arg.id()).arg(arg.sName()).arg(arg.sCompany()).arg(arg.sPlaces()).arg(arg.cFam()).arg(arg.cName()).arg(arg.cPatr());;

        QSqlQuery query(db);
        if (!query.exec(as)) emit dberror(query.lastError().text());
        else emit dbanswer("Данные о пароходе сохранены!");
    }
}

void DBproxy::find(steamer arg)

{
    QString q;
    QList<steamer> L;
    if (arg.sPlaces().isEmpty())
        q="select id, Название, Компания, Места, "
                "Фамилия, Имя, Отчество from steamer";
    else
    {
        q="select id, Название, Компания, Места, "
          "Фамилия, Имя, Отчество from steamer where Места like '";
        q+=arg.sPlaces();
        q+="' order by Название asc;";
    }
    //q+="' order by Название asc;";

    if (db.isOpen())
    {
        QSqlQuery query(db);
        if (!query.exec(q)) emit dbanswer(query.lastError().text());
    else
        while (query.next())
        {
             arg.setID(query.value(0).toString());
             arg.setSteamerName(query.value(1).toString());
             arg.setCompany(query.value(2).toString());
             arg.setPlaces(query.value(3).toString());
             arg.setCaptainFam(query.value(4).toString());
             arg.setCaptainName(query.value(5).toString());
             arg.setCaptainPatr(query.value(6).toString());
             L.push_back(arg);
         }
     }
     emit dbanswer(L);
     emit dbanswer("Выборка выполнена!");
}

void DBproxy::renewTable()
{
    model->select();
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    emit steamer_model(model);
}

