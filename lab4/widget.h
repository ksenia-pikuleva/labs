#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QEvent>
#include <QPainter>
#include <QBrush>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    void keyPressEvent(QKeyEvent* e);
    void paintEvent(QPaintEvent* e);

private:
    Ui::Widget *ui;
    int key = 0;
    int H, W;
    void drawBackground(QPainter& p, int key);
    void drawHeptagon(QPainter& p, int key);
};

#endif // WIDGET_H
