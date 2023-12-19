#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(800, 650);
    setWindowTitle("Визуализация графа");

    interface = new Interface(this);
    pw = new PaintingWidget(this);
    interface->setPaintingWidget(pw);
}

Widget::~Widget()
{
    delete interface;
    delete pw;
}

