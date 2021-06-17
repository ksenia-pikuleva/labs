#include "mainwindow.h"

#include <QApplication>
#include "dispatcher.h"
#include "generator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("pikulevaksen");
    QCoreApplication::setApplicationName("lab_work_7");
    MainWindow w;
    dispatcher d;   // создаем объект диспетчера
    generator G(d.counts);

    QObject::connect(&w, SIGNAL(start()), &G, SLOT(start()));
    QObject::connect(&w, SIGNAL(stop()), &G, SLOT(stop()));
    QObject::connect(&w, SIGNAL(acqprefs()), &d, SLOT(sendPrefs()));
    QObject::connect(&w, SIGNAL(finish()), &d, SLOT(finish()));

    QObject::connect(&w, SIGNAL(newCounter(counter)), &d, SLOT(add(counter)));
    QObject::connect(&w, SIGNAL(acqlist()), &d, SLOT(sendList()));
    QObject::connect(&w, SIGNAL(acqlog()), &d, SLOT(sendLog()));
    QObject::connect(&w, SIGNAL(answer(QString)), &d, SLOT(toLog(QString)));
    QObject::connect(&d, SIGNAL(answer(QString)), &w, SLOT(showStatus(QString)));
    QObject::connect(&d, SIGNAL(data(QString)), &w, SLOT(showData(QString)));
    w.show();
    return a.exec();
}
