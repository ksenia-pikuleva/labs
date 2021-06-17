#ifndef FORM1_H
#define FORM1_H

#include <QWidget>
#include "reader.h"
#include <qstandarditemmodel.h>
#include "tmcompleter.h"

namespace Ui {
class Form1;
}

class Form1 : public QWidget
{
    Q_OBJECT

public:
    explicit Form1(QWidget *parent = 0);
    ~Form1();
private:
    Ui::Form1 *ui;
    reader current_reader, model_reader;
    QCompleter::CompletionMode mode;
    TreeModelCompleter *completer;
    void checkInput(const QString &arg1);
signals:
    void check();
    void find(reader);
    void objectReady(reader);
    void showMessage(QString);
public slots:
    void handleData(QList<reader>);
private slots:
    void on_lineEdit_textEdited(const QString &arg1);
    void on_comboBox_currentIndexChanged(int index);

};

#endif // FORM1_H
