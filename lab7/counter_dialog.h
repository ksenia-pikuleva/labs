#ifndef COUNTER_DIALOG_H
#define COUNTER_DIALOG_H

#include <QDialog>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QRegExpValidator>
#include "counter.h"

// диалоговое окно для добавления счетчика

namespace Ui {
class counter_dialog;
}

class counter_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit counter_dialog(QWidget *parent = nullptr);
    ~counter_dialog();

protected:
    void accept(); // метод при нажатии ОК на окне диалога

private:
    Ui::counter_dialog *ui;
signals:
    void newCounter(counter);
};

#endif // COUNTER_DIALOG_H
