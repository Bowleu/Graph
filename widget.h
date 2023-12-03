#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "interface.h"
#include "paintingwidget.h"

class Widget : public QWidget
{
    Q_OBJECT
    Interface* interface;
    PaintingWidget* pw;

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
};
#endif // WIDGET_H
