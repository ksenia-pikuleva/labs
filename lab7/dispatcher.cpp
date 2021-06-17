#include "dispatcher.h"

dispatcher::dispatcher(QObject *parent) : QObject(parent)        // синглтон
{
    logfile = new QFile("events.log");                           // связываем имя файла с объектом
    if (logfile->exists()) toLog("начало работы программы");     // если файл  существует - выводим сообщение в журнал
    else if (logfile->open(QFile::WriteOnly)) logfile->close();  // если нет - создаем в режиме только запись

    m_settings = new QSettings("pikulevaksen", "lab7");
    m_settings->beginGroup("Counters");
    foreach (QString s, m_settings->allKeys())
        {
            counts[s.toInt()]=m_settings->value(s).toFloat();
        }
    m_settings->endGroup();

}

void dispatcher::add(counter c) // заносит сведения о добавляемом счетчике в ассоциативный массив
{
    QString s = "счетчик %1 добавлен в список";
    s = s.arg(QString::number(c.number));
    counts[c.number]=c.energy;                    // добавляет в массив
    emit answer(s);                               // высылает сигнал answer со строкой
    toLog(s);                                     // записывает строку в журнал

}

void dispatcher::toLog(QString s) // запись в журнал строки
{
    if (logfile->open(QFile::Append)) // открывает
    {
        log.setDevice(logfile);       // связывает объект с потоком
        log << QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss")<< "    " << s << "\n";
        logfile->close();
    }
    else emit answer("не могу открыть \"events.log\" для записи!");
}

void dispatcher::sendLog() // считывание файла журнала в строку
{
    toLog("вызван просмотр журнала работы");
    QString s = "журнал работы приложения:\n";
    if (logfile->open(QFile::ReadOnly))
    {
        log.setDevice(logfile);
        while (!log.atEnd())
            s += log.readLine()+"\n";
        logfile->close();
        emit data(s);  // высылает сигнал с накопленной строкой
    }
    else emit answer("не могу открыть \"events.log\" для чтения!");
}

void dispatcher::sendList() //  перебор массива
{
    toLog("вызван просмотр списка счетчиков");
    QString s;
    QMap<quint16, float>::iterator i;
    for (i=counts.begin(); i!=counts.end(); i++)
        s+="счетчик "+QString::number(i.key())+ " показания "+QString::number(i.value(),'f',2)+"\n";
    emit data(s); // сформированная сторка отправляется к списку
}

dispatcher::~dispatcher() // перед уничтожением записывает в журнал сообщение
{
    toLog("завершение работы программы");
}

void dispatcher::finish()
{
    QMap<quint16, float>::iterator ci = counts.begin();
    m_settings->beginGroup("Counters");
    for (;ci!=counts.end(); ci++)
        m_settings->setValue(QString::number(ci.key()), ci.value());
    m_settings->endGroup();
    toLog("завершение работы программы");
}

void dispatcher::sendPrefs() // перебор перечня настроек приложения
{
    toLog("вызван просмотр настроек программы");
    m_settings->beginGroup("Counters");
    QString res = "настройки:\n";
    foreach (QString s, m_settings->allKeys())
    {
        res+=s+" "+m_settings->value(s).toString()+"\n";
    }
    m_settings->endGroup();
    emit data(res);
}
