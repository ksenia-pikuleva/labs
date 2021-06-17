#ifndef GENERATOR_H
#define GENERATOR_H

#include <QObject>
#include <QTimer>
#include <QMap>

// генерируетпоказания счетчиков

class generator : public QObject
{
    Q_OBJECT
public:
    explicit generator(QMap<quint16, float>&);
    ~generator();
private:
    QTimer *t;
    QMap<quint16, float>& counts; // ссылка н ассоциативный массив
                                  // обязательно должна быть явно инициализирована
                                  // при объявлении формального аргумента функции, если не нужна копия фактического аргумента
                                  // ссылка инициализируется фактическим аргументом
signals:
    void answer(QString);
    void finished();
public slots:
    void start();
    void stop();
    void nextEvent();
};


#endif // GENERATOR_H
