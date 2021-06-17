#include "counter_dialog.h"
#include "ui_counter_dialog.h"

counter_dialog::counter_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::counter_dialog)
{
    ui->setupUi(this);
    QRegExp rx("[0-9]{1,3}\\.\\d{0,2}");
    QValidator* v1 = new QIntValidator(1, 2000, this); // создание объектов валидатора
    QValidator* v2 = new QRegExpValidator(rx, this);
    ui->lineEdit->setValidator(v1);                    // привязка валидаторов к полям ввода
    ui->lineEdit_2->setValidator(v2);
}

counter_dialog::~counter_dialog()
{
    delete ui;
}

void counter_dialog::accept() // переопределение ОК в окне диалога
{
    QDialog::accept();
    counter c;
    c.number=ui->lineEdit->text().toInt();
    c.energy=ui->lineEdit_2->text().toFloat();
    emit newCounter(c);
}
