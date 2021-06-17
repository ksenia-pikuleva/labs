#ifndef COUNTER_H
#define COUNTER_H

#include <QObject>

// счетчик

struct counter
{
    quint16 number; // номер счетчика
    float energy;   // показания счетчика
};

#endif // COUNTER_H
