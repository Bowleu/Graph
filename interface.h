#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include "paintingwidget.h"

class Interface : public QWidget
{
    Q_OBJECT

    QLineEdit* filePath;
    QPushButton* showGraph;
    QLabel *interfaceHeader, *messageHeader, *message, *showGraphHeader;
    PaintingWidget* pw;
public:
    Interface(QWidget *parent = nullptr);
    void setPaintingWidget(PaintingWidget* pw);
    ~Interface();
public slots:
    void updateGraph();
};

#endif // INTERFACE_H
