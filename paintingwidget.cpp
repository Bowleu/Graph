#include "paintingwidget.h"
#include <QStyleOption>
#include <QPainter>
#include <QtMath>

void PaintingWidget::paintEvent(QPaintEvent *event)
{
    int count = g->size();
    if (!count)
        return;
    QRect r = rect();
    qreal cw = 0.5*r.width();
    qreal ch = 0.5*r.height();
    qreal cr = 0.75*(cw>ch?ch:cw);
    qreal a = 2.0*acos(-1.0)/count;
    QPainter painter(this);
    if (centers)
        delete [] centers;
    centers = new QPointF[count];
    for (int i=0; i<count; i++)
    {
        QPointF center = QPointF(cw+cr*sin(i*a), ch-cr*cos(i*a));
        centers[i] = center + QPointF(250 / (qreal) count / 2, 250 / (qreal) count / 2);
        QRectF circleRect(center.x(), center.y(), 250 / count, 250 / count);
        painter.drawEllipse(circleRect);
        QFont font;
        qreal cf = 0.125*cr;
        font.setPointSize(cf);
        font.setBold(true);
        painter.setFont(font);
        painter.drawText(circleRect, Qt::AlignCenter, QString().setNum(i + 1));
    }
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            if (i != j and g->element(i, j) != 0) {
                qreal dist = qPow(qPow(centers[j].x() - centers[i].x(), 2) + qPow(centers[j].y() - centers[i].y(), 2), 0.5);
                qreal cosFi = (centers[j].x() - centers[i].x()) / dist;
                qreal sinFi = (centers[j].y() - centers[i].y()) / dist;
                QPointF borderDist = {250 / (qreal) count / 2 * cosFi, 250 / (qreal) count / 2 * sinFi};
                drawLineWithArrow(painter, centers[i] + borderDist, centers[j] - borderDist);
            }
        }
    }
    painter.end();
}

void PaintingWidget::drawLineWithArrow(QPainter& painter, QPointF start, QPointF end) {
    qreal arrowSize = 10;
    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);
    QLineF line(end, start);
    double angle = std::atan2(-line.dy(), line.dx());
    QPointF arrowP1 = line.p1() + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                          cos(angle + M_PI / 3) * arrowSize);
    QPointF arrowP2 = line.p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                          cos(angle + M_PI - M_PI / 3) * arrowSize);

    QPolygonF arrowHead;
    arrowHead.clear();
    arrowHead << line.p1() << arrowP1 << arrowP2;
    painter.drawLine(line);
    painter.drawPolygon(arrowHead);

}

PaintingWidget::PaintingWidget(QWidget *parent) : QWidget(parent)
{
    g = new Graph();
    setGeometry(220, 10, 570, 580);
}
void PaintingWidget::changeGraph(QVector<int> values) {
    if (g)
        delete g;
    g = new Graph(values);
    int a = 0;
    a++;
    update();
}

PaintingWidget::~PaintingWidget() {
    if (g)
        delete g;
    if (centers)
        delete [] centers;
}

