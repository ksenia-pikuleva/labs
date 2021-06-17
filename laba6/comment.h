#ifndef comment_H
#define comment_H
#include <qdatetime.h>

class comment
{
private:
    QString id_req, id_cust, req_text;
    QDateTime req_dt;
public:
    void setreaderId(QString);
    void setText(QString);
    void setDT(QDateTime);
    QDateTime dt();
    QString text();
    QString id();
    QString readerId();
    comment();
    ~comment();

};

#endif // comment_H
