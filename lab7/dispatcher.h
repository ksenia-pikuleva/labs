#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <QObject>
#include "counter.h"
#include <qfile.h>
#include <qdatetime.h>
#include <qtextstream.h>
#include <QSettings>

// класс формирует список счетчиков и журнал действий
// хранит словарь: номер счетчика-показания - массив
// взаимодействие с файлом журнала
// сохранение настроек приложения между его вызовами

class dispatcher : public QObject
{
    Q_OBJECT
public:
    explicit dispatcher(QObject *parent = 0);
    ~dispatcher();

    friend int main(int, char**);

private:
    QFile* logfile;
    QTextStream log;
    QMap<quint16, float> counts;
    QSettings* m_settings; // объект для работы с настройками
                           // обеспечивает платформменно-независимое хранение настроек программы
signals:
    void data(QString);   // передача справочной информации
    void answer(QString); // передача кратких уведомлений оконному объекту
public slots:
    void finish();
    void add(counter);
    void toLog(QString);
    void sendPrefs();
    void sendList();
    void sendLog();
};

#endif // DISPATCHER_H
