#include "steamer.h"

steamer::steamer()
{
   m_id = "0";
}

steamer::~steamer()
{

}

bool steamer::is_correct(QString s)
{
    for (int i=0; i<s.length(); i++)
            if (!(s[i].isLetter()||s[i]=='-')) return false;
        return true;
}

bool steamer::is_sufficient()
{
    return !(m_sname.isEmpty());
}



int steamer::setSteamerName(QString s)
{
    s=s.simplified();
    if (is_correct(s))
        {
            m_sname=s;
            return 1;
        }
        else return 0;
}

int steamer::setCaptainFam(QString s)
{
    s=s.simplified();
    if (is_correct(s))
        {
            m_cfam=s;
            return 1;
        }
        else return 0;
}

int steamer::setCaptainName(QString s)
{
    s=s.simplified();
    if (is_correct(s))
        {
            m_cname=s;
            return 1;
        }
        else return 0;

}

int steamer::setCaptainPatr(QString s)
{
    s=s.simplified();
    if (is_correct(s))
        {
            m_cpatr=s;
            return 1;
        }
        else return 0;
}

int steamer::setCompany(QString s)
{
    s=s.simplified();
    if (is_correct(s))
        {
            m_company=s;
            return 1;
        }
        else return 0;
}

int steamer::setPlaces(QString p)
{
     m_places=p;
     return 1;
}

void steamer::setID(QString id)
{
    m_id = id;
}


QString steamer::cFam()
{
    return m_cfam;
}

QString steamer::cName()
{
    return m_cname;
}

QString steamer::cPatr()
{
    return m_cpatr;
}

QString steamer::sName()
{
    return m_sname;
}

QString steamer::sPlaces()
{
    return m_places;
}

QString steamer::id()
{
    return m_id;
}

QString steamer::sCompany()
{
    return m_company;
}
