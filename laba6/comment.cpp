#include "comment.h"
comment::comment()
{
    id_req="0";
}
void comment::setreaderId(QString id)
{
    bool ok;
    id.toInt(&ok);
    if (ok) id_cust=id;
}
void comment::setText(QString t)
{
    req_text=t;
}
void comment::setDT(QDateTime dt)
{
    req_dt=dt;
}
QDateTime comment::dt()
{
    return req_dt;
}
QString comment::text()
{
    return req_text;
}
QString comment::id()
{
    return id_req;
}
QString comment::readerId()
{
    return id_cust;
}

comment::~comment()
{

}
