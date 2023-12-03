#ifndef PAINTINGWIDGET_H
#define PAINTINGWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include "graph.h"

class PaintingWidget : public QWidget
{
    Q_OBJECT
    Graph *g;
    QPointF* centers;
    void drawLineWithArrow(QPainter& painter, QPointF start, QPointF end);
protected:
    void paintEvent(QPaintEvent* event);
public:
    PaintingWidget(QWidget *parent = nullptr);
    void changeGraph(QVector<int> values);
    ~PaintingWidget();
};

#endif // PAINTINGWIDGET_H
