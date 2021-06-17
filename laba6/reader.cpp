#include "reader.h"

reader::reader()
{
    m_id="0";
}
int reader::setFamily(QString s)
{
    s=s.simplified();
    if (isCorrect(s))
    {
        m_family=s;
        return 1;
    }
    else return 0;
}
int reader::setName(QString s)
{
    s=s.simplified();
    if (isCorrect(s))
    {
        m_name=s;
        return 1;
    }
    else return 0;
}
int reader::setPatronymic(QString s)
{
    s=s.simplified();
    if (isCorrect(s))
    {
        m_patronymic=s;
        return 1;
    }
    else return 0;
}

int reader::setPhone(QString num)
{
    int i=0;
    if (num.startsWith('+')) i=1;
    for (; i<num.length(); i++)
        if (!num[i].isDigit()) return 0;
    m_phone=num;
    return 1;
}
void reader::setId(QString id)
{
    m_id=id;
}
int reader::setNum(QString s)
{
    m_num=s;
    return 1;
}
bool reader::isCorrect(QString s)
{
    for (int i=0; i<s.length(); i++)
        if (!(s[i].isLetter()||s[i]=='-')) return false;
    return true;
}
bool reader::isSufficient()
{
    return !(m_family.isEmpty()||m_name.isEmpty());
}
QString reader::family()
{
    return m_family;
}
QString reader::name()
{
    return m_name;
}
QString reader::patronymic()
{
    return m_patronymic;
}
QString reader::num()
{
    return m_num;
}
QString reader::phone()
{
    return m_phone;
}

QString reader::id()
{
    return m_id;
}
reader::~reader()
{
}
bool reader::operator==(reader& arg)
{
    return ((m_family==arg.m_family)&&(m_name==arg.m_name)
        &&(m_patronymic==arg.m_patronymic));
}
