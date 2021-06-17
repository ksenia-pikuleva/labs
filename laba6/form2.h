#ifndef FORM2_H
#define FORM2_H

#include <QWidget>
#include <reader.h>
#include <qstandarditemmodel.h>
#include <tmcompleter.h>
#include <comment.h>
#include <dbproxy.h>
namespace Ui {
class Form2;
}
class Form2 : public QWidget
{
        Q_OBJECT
public:
    explicit Form2(QWidget *parent = nullptr);
    ~Form2();
private:
    Ui::Form2 *ui;
    reader current_reader, model_reader;
    QCompleter::CompletionMode mode;
    TreeModelCompleter *completer;
    QModelIndex current_element;
    QMap<QString, reader> M;
    void checkInput(const QString &arg1);
signals:
    void check();
    void find(reader);
    void objectReady(reader);
    void objectReady(comment);
    void showMessage(QString);
public slots:
    void handleData(QList<reader>);
    void createcomment(reader);
private slots:
    void highlight(const QModelIndex&);
    void on_pushButton_clicked();
    void on_lineEdit_returnPressed();
    void on_lineEdit_textEdited(const QString &arg1);
    void on_comboBox_currentIndexChanged(int index);

};


#endif // Form2_H
