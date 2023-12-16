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

    QLineEdit* filePath, *activeNode;
    QPushButton* showGraph, *turnCCW, *turnCW;
    QLabel *interfaceHeader, *messageHeader, *message, *showGraphHeader, *activeNodeHeader;
    PaintingWidget* pw;
public:
    Interface(QWidget *parent = nullptr);
    void setPaintingWidget(PaintingWidget* pw);
    ~Interface();
public slots:
    void updateGraph();
    void decrementActive();
    void incrementActive();
};

#endif // INTERFACE_H
