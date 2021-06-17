#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_2_triggered()
{
    Form2* F1 = new Form2();
    connect(this, SIGNAL(dbanswer(QList<reader>)), F1, SLOT(handleData(QList<reader>)));
    connect(this, SIGNAL(dbanswer(reader)), F1, SLOT(createcomment(reader)));
    connect(F1, SIGNAL(find(reader)), this, SIGNAL(find(reader)));
    connect(F1, SIGNAL(objectReady(reader)), this, SIGNAL(objectReady(reader)));
    connect(F1, SIGNAL(objectReady(comment)), this, SIGNAL(objectReady(comment)));
    connect(F1, SIGNAL(showMessage(QString)), this, SLOT(showMessage(QString)));
    setCentralWidget(F1);
}

void MainWindow::showEvent(QShowEvent* e)
{
    QMainWindow::showEvent(e);
    emit check();
}
void MainWindow::showMessage(QString s)
{
    ui->statusBar->showMessage(s, 3000);
}

void MainWindow::on_action_3_triggered()
{
    Form3* F3 = new Form3();
    connect(this, SIGNAL(reader_model(QSqlRelationalTableModel*)), F3, SLOT(setModel(QSqlRelationalTableModel*)));
    emit renewTable();
    setCentralWidget(F3);

}

void MainWindow::on_action_triggered()
{
    Form1* F1 = new Form1();
    connect(this, SIGNAL(dbanswer(QList<reader>)), F1, SLOT(handleData(QList<reader>)));
    connect(F1, SIGNAL(find(reader)), this, SIGNAL(find(reader)));
    connect(F1, SIGNAL(objectReady(reader)), this, SIGNAL(objectReady(reader)));
    connect(F1, SIGNAL(showMessage(QString)), this, SLOT(showMessage(QString)));
    setCentralWidget(F1);
}
