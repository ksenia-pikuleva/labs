#ifndef READER_H
#define READER_H
#include <qstring.h>
#include <qdatetime.h>

class reader
{
protected:
    QString m_family, m_name, m_patronymic, m_num, m_phone;
    QString m_id;
    bool isCorrect(QString);
public:
    reader();
    ~reader();
    bool isSufficient();
    int setFamily(QString);
    int setName(QString);
    int setPatronymic(QString);
    int setNum(QString);
    int setPhone(QString);
    void setId(QString);
    QString family();
    QString name();
    QString patronymic();
    QString num();
    QString phone();
    QString id();
    bool operator ==(reader& arg);
};

#endif // READER_H
