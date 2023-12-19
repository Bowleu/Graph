#ifndef PAINTINGWIDGET_H
#define PAINTINGWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include "stategraph.h"

class PaintingWidget : public QWidget
{
    Q_OBJECT
    StateGraph *g;
    QPointF* centers;
    void drawLineWithArrow(QPainter& painter, QPointF start, QPointF end);
protected:
    void paintEvent(QPaintEvent* event);
public:
    PaintingWidget(QWidget *parent = nullptr);
    void changeGraph(QVector<int> values, int activeNodeNum);
    void updateActive(bool value);
    ~PaintingWidget();
};

#endif // PAINTINGWIDGET_H
