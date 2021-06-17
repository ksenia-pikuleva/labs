#ifndef FORM3_H
#define FORM3_H

#include <QWidget>
#include <reader.h>
#include <dbproxy.h>
#include <comment.h>
namespace Ui {
class Form3;
}

class Form3 : public QWidget
{
    Q_OBJECT

public:
    explicit Form3(QWidget *parent = nullptr);
    ~Form3();

private:
    Ui::Form3 *ui;
public slots:
    void setModel(QSqlRelationalTableModel*);
};

#endif // FORM3_H
