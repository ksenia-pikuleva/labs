#include "tabwidget.h"
#include "ui_tabwidget.h"
#include <QMessageBox>

TabWidget::TabWidget(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::TabWidget)
{
    ui->setupUi(this);
}
TabWidget::~TabWidget()
{
    delete ui;
}

void TabWidget::on_pushButton_clicked() // кнопака Сохранить
{
    steamer s; bool ok;
    ok = s.setSteamerName(ui->lineEdit->text())&&
         s.setCompany(ui->lineEdit_6->text())&&
         s.setPlaces(ui->lineEdit_5->text())&&
         s.setCaptainFam(ui->lineEdit_2->text())&&
         s.setCaptainName(ui->lineEdit_3->text())&&
         s.setCaptainPatr(ui->lineEdit_4->text());
    if (!ok)
    {
        QMessageBox::warning(this, "Ошибка ввода данных", "Недопустимые значения!");
        return;
    }
    if (!s.is_sufficient())
    {
        QMessageBox::warning(this, "Предупреждение", "Недостаточные сведения!");
        return;
    }
    emit objectReady(s);
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
    ui->lineEdit->setFocus();
}

void TabWidget::on_lineEdit_7_returnPressed()  // выполнение поиска
{
    steamer s;
    if (!s.setPlaces(ui->lineEdit_7->text())) return;
    ui->lineEdit_7->clear();
    ui->lineEdit_7->setFocus();
    emit find(s);
}

void TabWidget::showData(QList<steamer> L)
{
    ui->tableWidget->setRowCount(L.count());
    ui->tableWidget->clearContents();
    quint16 row = 0;
    QTableWidgetItem *newItem;
    foreach (steamer s, L)
    {
        newItem = new QTableWidgetItem(s.sName());
        ui->tableWidget->setItem(row, 0, newItem);
        newItem = new QTableWidgetItem(s.sCompany());
        ui->tableWidget->setItem(row, 1, newItem);
        newItem = new QTableWidgetItem(s.sPlaces());
        ui->tableWidget->setItem(row, 2, newItem);
        newItem = new QTableWidgetItem(s.cFam());
        ui->tableWidget->setItem(row, 3, newItem);
        newItem = new QTableWidgetItem(s.cName());
        ui->tableWidget->setItem(row, 4, newItem);
        newItem = new QTableWidgetItem(s.cPatr());
        ui->tableWidget->setItem(row, 5, newItem);
        row++;
    }
}

void TabWidget::showEvent(QShowEvent* e) // при отображении окна формы
{
    QTabWidget::showEvent(e);
    emit check();
    resizeTables();
}

void TabWidget::resizeEvent(QResizeEvent *e) // при изменении размеров окна
{
    QTabWidget::resizeEvent(e);
    resizeTables();
}

void TabWidget::resizeTables() // настройка ширины столбцов
{
    int w = ui->tableWidget->width()/5;
    for (int i=0; i<6; i++)
        ui->tableWidget->setColumnWidth(i,w);
    w = ui->tableView->width()/6;
    for (int i=0; i<7; i++)
        ui->tableView->setColumnWidth(i,w);
}

void TabWidget::showTables(QStringList L) // добавляет таблицы из списка к надписи
{
    foreach (QString str, L)
    {
        ui->label_9->setText(ui->label_9->text()+str+'\n');
    }
}

void TabWidget::showMessage(QString m) // ввод сообщений
{
    ui->plainTextEdit->appendPlainText(m);
}

void TabWidget::on_TabWidget_currentChanged(int index) // при смене вкладок обновление данных таблицы
{
    if (index==3) emit renewTable();
    resizeTables();
}
void TabWidget::setModel(QSqlTableModel* m) // привязка табличной модели к графическому интерфейсу на вкладке
{
    ui->tableView->setModel(m);
}


