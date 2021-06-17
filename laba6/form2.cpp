#include "form2.h"
#include "ui_form2.h"

Form2::Form2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form2)
{
    ui->setupUi(this);
    mode = QCompleter::InlineCompletion;
}


Form2::~Form2()
{
    delete ui;
}

void Form2::on_lineEdit_textEdited(const QString &arg1)
{
    checkInput(arg1);
}

void Form2::checkInput(const QString &arg1)
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

void Form2::on_comboBox_currentIndexChanged(int index)
{
    switch (index)
    {
        case 0:  mode = QCompleter::InlineCompletion; break;
        case 1:  mode = QCompleter::PopupCompletion; break;
        default: mode = QCompleter::UnfilteredPopupCompletion;
    }
}
void Form2::handleData(QList<reader> L)
{
    static QStandardItemModel model;
    model.clear(); M.clear();
    QString sf, sn, sp;
    QStringList slf, sln, slp;
    QStandardItem *item, *upperItem, *prevFItem=nullptr, *prevNItem=nullptr, *prevPItem=nullptr;
    QList<reader>::iterator i;
    for (i=L.begin(); i!=L.end(); i++)
    {
        M[i->id()]=*i;
        if (i->family()!=sf)
        {
            if (prevFItem)
                prevFItem->setData(slf);
            slf.clear();
            item = new QStandardItem(i->family());
            model.invisibleRootItem()->appendRow(item);
            prevFItem = item;
        }
        else
        {
            item=prevFItem;
        }
        slf.push_back(i->id());
        upperItem = item;
        if (i->name()!=sn)
        {
            if (prevNItem)
                prevNItem->setData(sln);
            sln.clear();
            item = new QStandardItem(i->name());
            upperItem->appendRow(item);
            prevNItem = item;
        }
        else
        {
            item=prevNItem;
        }
        sln.push_back(i->id());
        upperItem = item;
        if (i->patronymic()!=sp)
        {
            if (prevPItem)
                prevPItem->setData(slp);
            slp.clear();
            item = new QStandardItem(i->patronymic());
            upperItem->appendRow(item);
            prevPItem=item;
        }
        slp.push_back(i->id());
        sf=i->family();
        sn=i->name();
        sp=i->patronymic();
    }
    if (prevFItem) prevFItem->setData(slf);
    if (prevNItem) prevNItem->setData(sln);
    if (prevPItem) prevPItem->setData(slp);
    completer = new TreeModelCompleter(this);
    completer->setModel(&model);
    completer->setSeparator(QLatin1String(" "));
    completer->setCompletionMode(mode);
    completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    connect(completer, SIGNAL(highlighted(QModelIndex)), this, SLOT(highlight(QModelIndex)));
    ui->lineEdit->setCompleter(completer);
}
void Form2::highlight(const QModelIndex &index)
{
    QStringList id_list;
    if (index.isValid())
        id_list = index.data(Qt::UserRole+1).toStringList();
    if (id_list.count()==1) model_reader=M[id_list.front()];
}
void Form2::on_lineEdit_returnPressed()
{
    checkInput(ui->lineEdit->text());
}
void Form2::createcomment(reader c)
{
    current_reader=c;
    comment r;
    r.setText(ui->plainTextEdit->toPlainText());
    r.setreaderId(current_reader.id());
    r.setDT(QDateTime::currentDateTime());
    emit objectReady(r);
}

void Form2::on_pushButton_clicked()
{
    if (!current_reader.isSufficient())
    {
        emit showMessage("необходимо указать фамилию и имя!");
        return;
    }
    if (current_reader==model_reader)
        createcomment(model_reader);
    else
    {
        current_reader.setId("0");
        emit objectReady(current_reader);
    }
}

