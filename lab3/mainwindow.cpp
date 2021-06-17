#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->spinBox->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->lineEdit->clear();
    ui->spinBox->setValue(0);
    ui->progressBar->setValue(0);
    ui->lineEdit->setFocus();
}

void MainWindow::change_all_values(QString str)
{
    int val = str.length();
    ui->spinBox->setValue(val);
    ui->progressBar->setValue(val);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (QMessageBox::question(this, QString(), "Завершить приложение?", QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes)
        event->accept();
    else
        event->ignore();
}

