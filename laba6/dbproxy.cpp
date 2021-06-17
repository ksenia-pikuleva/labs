#include "dbproxy.h"

DBproxy* DBproxy::m_instance=nullptr;
DBproxy::DBproxy() : QObject(0)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QDir::homePath() + "/database.db");
    model = new QSqlRelationalTableModel(this);
}

DBproxy* DBproxy::getInstance()
{
    if (m_instance == nullptr) m_instance = new DBproxy();
    return m_instance;
}

void DBproxy::check()
{
    if (!db.open()) emit dberror(db.lastError().text());
    else
    {
        QString qstr1 = "create table if not exists `readers`"
        "(`id_read` INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
        "`family` VARCHAR(30), `name` VARCHAR(30), `patronymic` VARCHAR(30),"
        "`num` VARCHAR(200), `phone` VARCHAR(12));";
        QString qstr2 = "create table if not exists `comments`"
        "(`id_com` INTEGER PRIMARY KEY NOT NULL,"
        "`id_read` INTEGER, `com_text` VARCHAR(200), `com_dt` DATETIME);";
        QSqlQuery query(db);
        if (query.exec(qstr1))
            emit dbanswer("таблица `readers` создана или уже существует!");
        else emit dberror(query.lastError().text());
        if (query.exec(qstr2))
            emit dbanswer("таблица `comments` создана или уже существует!");
        else emit dberror(query.lastError().text());
           model->setTable("comments");
        model->setRelation(1, QSqlRelation("readers", "id_read", "family"));
        model->setSort(1, Qt::AscendingOrder);
    }
}

void DBproxy::status()
{
    emit dbanswer(db.tables());
}

void DBproxy::save(reader arg)
{
    QString as, qIns, qUpd, qMax;
    qIns="insert into `readers` (family, name, patronymic, "
         "num ,phone) values('%1', '%2', '%3', '%4', '%5');";
    qUpd="update readers set id_read='%1',family='%2', name='%3', "
         "patronymic='%4', num='%5', phone='%6' "
         "where id_read='%1';";
    qMax="select max(id_read) from `readers`;";
    if (db.isOpen())
    {
        QSqlQuery query(db);
        if (arg.id()=="0")
            as=qIns.arg(arg.family()).arg(arg.name()).arg(arg.patronymic()).arg(arg.num()).arg(arg.phone());
        else
            as=qUpd.arg(arg.id()).arg(arg.family()).arg(arg.name()).arg(arg.patronymic()).arg(arg.num()).arg(arg.phone());
        if (!query.exec(as)) emit dberror(query.lastError().text());
        else emit dbanswer("данные о пользователе сохранены!");
        if (arg.id()=="0")
        {
            query.exec(qMax);
            if (query.next())
            {
                arg.setId(query.value(0).toString());
                emit dbanswer(arg);
            }
        }
    }
}

void DBproxy::save(comment arg)
{
    QString as, qIns, qUpd;
    qIns="insert into `comments` (id_read, com_text, com_dt) "
         "values('%1', '%2', '%3')";
    qUpd="update `comments` set id_com='%1',id_read='%2', "
         "com_text='%3', com_dt='%4' where id_com='%1';";
    if (db.isOpen())
    {
        if (arg.id()=="0")         as=qIns.arg(arg.readerId()).arg(arg.text()).arg(arg.dt().toString("yyyy-MM-dd hh:mm:ss"));
        else            as=qUpd.arg(arg.id()).arg(arg.readerId()).arg(arg.text()).arg(arg.dt().toString("yyyy-MM-dd hh:mm:ss"));
        QSqlQuery query(db);
        if (!query.exec(as)) emit dberror(query.lastError().text());
        else emit dbanswer("данные о пользователе сохранены!");
    }
}

void DBproxy::find(reader arg)
{
    QString q;
    QList<reader> L;
    if (arg.family().isEmpty())
        q="select id_read, family, name, patronymic, "
          "num, phone from readers";
    else
    {
        q="select id_read, family, name, patronymic, "
          "num, phone from readers where family like '";
        q+=arg.family()+"%'";
    }
    q+=" order by family, name, patronymic asc;";
    if (db.isOpen())
    {
        QSqlQuery query(db);
        if (!query.exec(q)) emit dbanswer(query.lastError().text());
        else
            while (query.next())
            {
                arg.setId(query.value(0).toString());
                arg.setFamily(query.value(1).toString());
                arg.setName(query.value(2).toString());
                arg.setPatronymic(query.value(3).toString());
                arg.setNum(query.value(4).toString());
                arg.setPhone(query.value(5).toString());
                L.push_back(arg);
            }
    }
    emit dbanswer(L);
    emit dbanswer("выборка выполнена!");
}

void DBproxy::renewTable()
{
    model->select();
    model->setEditStrategy(QSqlRelationalTableModel::OnFieldChange);
    emit reader_model(model);
}
