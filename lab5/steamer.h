#ifndef STEAMER_H
#define STEAMER_H

#include <QString>

class steamer
{
protected:
    QString m_id;
    QString m_sname, m_company;
    QString m_places;
    QString m_cfam, m_cname, m_cpatr;
    bool is_correct(QString);
public:
    steamer();
    ~steamer();
    bool is_sufficient();

    void setID(QString);
    int setSteamerName(QString);
    int setCompany(QString);
    int setPlaces(QString);
    int setCaptainFam(QString);
    int setCaptainName(QString);
    int setCaptainPatr(QString);

    QString id();
    QString sName();
    QString sCompany();
    QString sPlaces();
    QString cFam();
    QString cName();
    QString cPatr();

};

#endif // STEAMER_H
