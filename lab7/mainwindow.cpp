#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "counter_dialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    list= new QAction(QIcon(":/image/list"), tr("List of counters"), this); // объекты действий
    add = new QAction(QIcon(":/image/add"), tr("Add counter"), this);       // с пиктограммой
    run = new QAction(QIcon(":/image/start"), tr("Start"), this);           // подсказкой
    jrn = new QAction(QIcon(":/image/journal"), tr("Log file"), this);      // и указателем на объект-родитель для удаления

    connect(add, SIGNAL(triggered()), this, SLOT(addCounter()));            // вызов addCounter при нажатии кнопки "+"
    connect(run, SIGNAL(triggered()), this, SLOT(runProcess()));            // вызов runProcess при нажатии start
    connect(list, SIGNAL(triggered()), this, SIGNAL(acqlist()));            // список счетчиков
    connect(jrn, SIGNAL(triggered()), this, SIGNAL(acqlog()));              // журнал

    run->setStatusTip(tr("Start counters!")); // подсказка в строке статуса
    ui->mainToolBar->addAction(run);          // добавление инструментов в панель
    ui->mainToolBar->addAction(add);
    ui->mainToolBar->addAction(list);
    ui->mainToolBar->addAction(jrn);
    setIconSize(QSize(64,64));                // масштабирование пиктограмм
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addCounter() // слот для добавления нового счетчика
{
    counter_dialog* pd = new counter_dialog(this);
    connect(pd, SIGNAL(newCounter(counter)), this, SIGNAL(newCounter(counter)));
    pd->exec();   // отображение диалогового окна + возвращает результат от ОК или ОТМЕНА
}

void MainWindow::runProcess() // кнопки старт\стоп
{
    static bool st=true;
    if (st) //если нажали "Старт", икону меняем на "Стоп"
    {
        run->setIcon(QIcon(":/image/stop"));
        run->setToolTip(tr("STOP"));
        run->setStatusTip("Запуск работы счетчиков");
        emit start();
        emit answer("запуск процесса");
    }
    else //если нажали "Стоп", икону меняем на "Старт"
    {
        run->setIcon(QIcon(":/image/start"));
        run->setToolTip(tr("START"));
        run->setStatusTip("Останов работы счетчиков");
        emit stop();
        emit answer("останов процесса");
    }
    st=!st;
}

void MainWindow::showStatus(QString s)
{
    ui->statusbar->showMessage(s, 3000);
}

void MainWindow::showData(QString s)
{
    QTextEdit* te = new QTextEdit(this);
    te->setText(s);
    setCentralWidget(te);
}

void MainWindow::showEvent(QShowEvent *event)
{
    emit acqprefs();
    QMainWindow::showEvent(event);
}
void MainWindow::closeEvent(QCloseEvent * event)
{
    emit finish();
    QMainWindow::closeEvent(event);
}

