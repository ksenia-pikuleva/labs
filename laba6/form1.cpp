#include "form1.h"
#include "ui_form1.h"

Form1::Form1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form1)
{
    ui->setupUi(this);
    mode = QCompleter::InlineCompletion;
}


Form1::~Form1()
{
    delete ui;
}
void Form1::checkInput(const QString &arg1)
{
    QString s = arg1.simplified();
    bool ok = current_reader.setFamily(s.section(" ", 0, 0))&&
              current_reader.setName(s.section(" ", 1, 1))&&
              current_reader.setPatronymic(s.section(" ", 2, 2));
    if (!ok)
    {
        emit showMessage("Недопустимые символы ФИО!"); return;
    }
    if ((current_reader.family().length()>1) && (!arg1.contains(" ")))
        emit find(current_reader);
}

void Form1::on_lineEdit_textEdited(const QString &arg1)
{
    checkInput(arg1);
}

void Form1::handleData(QList<reader> L)
{
    static QStandardItemModel model;
    model.clear();
    QString sf, sn, sp;
    QStandardItem *item, *upperItem, *prevFItem=nullptr, *prevNItem=nullptr;
    QList<reader>::iterator i;
    for (i=L.begin(); i!=L.end(); i++)
        {
            if (i->family()!=sf)
            {
                item = new QStandardItem(i->family());
                model.invisibleRootItem()->appendRow(item);
                prevFItem = item;
            }
            else
            {
                item=prevFItem;
            }
            upperItem = item;
            if (i->name()!=sn)
            {
                item = new QStandardItem(i->name());
                upperItem->appendRow(item);
                prevNItem = item;
            }
            else
            {
                item=prevNItem;
            }
            upperItem = item;
            if (i->patronymic()!=sp)
            {
                item = new QStandardItem(i->patronymic());
                upperItem->appendRow(item);
            }
            sf=i->family();
            sn=i->name();
            sp=i->patronymic();
        }
        completer = new TreeModelCompleter(this);
        completer->setModel(&model);
        completer->setSeparator(QLatin1String(" "));
        completer->setCompletionMode(mode);
        completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
        ui->lineEdit->setCompleter(completer);
        ui->treeView->setModel(&model);
        ui->treeView->expandAll();
}

void Form1::on_comboBox_currentIndexChanged(int index)
{
    switch (index)
    {
        case 0:  mode = QCompleter::InlineCompletion; break;
        case 1:  mode = QCompleter::PopupCompletion; break;
        default: mode = QCompleter::UnfilteredPopupCompletion;
    }
}


