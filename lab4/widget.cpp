#include "widget.h"
#include "ui_widget.h"
#include <QWidget>
#include <QKeyEvent>
#include <QPainter>
#include <QBrush>
#include <QPolygon>
#include <QtMath>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent *e)
{
    QString str = e->text();
    key = str.toInt();
    update();
}

void Widget::paintEvent(QPaintEvent*)
{
    static int c=0;
    W=this->size().width();
    H=this->size().height();
    this->setWindowTitle("Paint event counter: "+QString::number(c));
    c++;
    QPainter painter;
    painter.begin(this);
        drawBackground(painter, key);
        drawHeptagon(painter, key);
    painter.end(); 
}

void Widget::drawBackground(QPainter& painter, int key)
{
    QBrush brush;
    switch (key)
    {
        case 1: painter.setBrush(QBrush(Qt::red)); break;
        case 2: painter.setBrush(QBrush(Qt::gray)); break;
        case 3: painter.setBrush(QBrush(Qt::yellow)); break;
        case 4: painter.setBrush(QBrush(Qt::green)); break;
        case 5: painter.setBrush(QBrush(Qt::cyan)); break;
        case 6: painter.setBrush(QBrush(Qt::blue)); break;
        case 7: painter.setBrush(QBrush(Qt::darkMagenta)); break;
        default: painter.setBrush(QBrush(Qt::white)); break;
    }
    painter.drawRect(rect());
}

void Widget::drawHeptagon(QPainter& painter, int key)
{
    int R, x0, y0;
    int N = 7;
    QColor color;
    QVector<QPoint> PL;
    painter.setRenderHint(QPainter::Antialiasing, true);
    R=rand()%100+50;
    color.setRgb(rand()%256,rand()%256,rand()%256);
    painter.setPen(color);

    QPixmap pic1("D:/Qt-projects/lab4/picture1.jpg");
    QPixmap pic2("D:/Qt-projects/lab4/picture2.jpg");
    QPixmap pic3("D:/Qt-projects/lab4/picture3.jpg");
    QPixmap pic4("D:/Qt-projects/lab4/picture4.jpg");
    QBrush brush;
    int picnum = rand()%4+1;
    switch (picnum)
    {
    case 1: brush.setTexture(pic1);break;
    case 2: brush.setTexture(pic2);break;
    case 3: brush.setTexture(pic3);break;
    case 4: brush.setTexture(pic4);break;
    default: brush.setTexture(pic1);break;
    }
    painter.setBrush(brush);

    x0=W/2;
    y0=H/2;
    for (int i=0; i<N; i++)
    {
        qreal fAngle = 2*M_PI*i/N;
        qreal x = x0 + cos(fAngle) * R;
        qreal y = y0 + sin(fAngle) * R;
        PL.push_back(QPoint(x,y));
    }
    QPolygon P(PL);
    painter.drawConvexPolygon(P);
    PL.clear();
}


