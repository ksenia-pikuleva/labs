#include "generator.h"

generator::generator(QMap<quint16, float>& ref) : counts(ref) // вызов конструктора копирования для атрибута counts
// инициализатор в конструкторе - инициализация ссылки
{
    srand(time(NULL));    // точка отсчета - системное время
    t = new QTimer(this);
    t->setInterval(1000);
    connect(t, SIGNAL(timeout()), this, SLOT(nextEvent()));
}

void generator::start() // запуск таймера для объекта, если список счетчиков не пуст
{
    if (counts.empty()) return;
    emit answer("Generator started!");
    t->start();
}

void generator::nextEvent()
{
    static quint16 p;
    QMap<quint16, float>::iterator ci = counts.begin();
    int num = rand()%counts.size();
    for (int i=0; i<num; i++, ci++);
    quint16 counter = ci.key();
    counts[counter]+= float(rand()%150)/100;
    p=rand()%8+2;
    t->setInterval(p*1000);
}

void generator::stop()
{
    t->stop();
    emit answer("Generator stoped!");
    emit finished();
}

generator::~generator() //объект таймера будет удален, когда управление вернется к циклу обработки событий приложения
{
    t->deleteLater();
}


