#include "interface.h"
#include <QFile>
#include <QDir>
#include <QRegularExpression>
#include <QStringList>

Interface::Interface(QWidget *parent) : QWidget(parent)
{
    setGeometry(10, 10, 800, 650);
    showGraph = new QPushButton(this);
    showGraph->setGeometry(5, 360, 190, 60);
    showGraph->setStyleSheet("font-size: 12pt;");
    showGraph->setText("Показать граф");
    filePath = new QLineEdit(this);
    filePath->setGeometry(5, 200, 190, 60);
    filePath->setStyleSheet("font-size: 12pt;");
    interfaceHeader = new QLabel(this);
    interfaceHeader->setGeometry(0, 40, 200, 60);
    interfaceHeader->setStyleSheet("font-weight: 800; font-size: 14pt;");
    interfaceHeader->setAlignment(Qt::AlignCenter);
    interfaceHeader->setText("Управление");
    messageHeader = new QLabel(this);
    messageHeader->setGeometry(0, 430, 200, 50);
    messageHeader->setStyleSheet("font-weight: 800; font-size: 14pt;");
    messageHeader->setAlignment(Qt::AlignCenter);
    messageHeader->setText("Сообщение");
    showGraphHeader = new QLabel(this);
    showGraphHeader->setGeometry(5, 140, 190, 50);
    showGraphHeader->setStyleSheet("font-size: 14pt;");
    showGraphHeader->setAlignment(Qt::AlignCenter);
    showGraphHeader->setWordWrap(true);
    showGraphHeader->setText("Введите путь к файлу: ");
    message = new QLabel(this);
    message->setGeometry(5, 480, 190, 160);
    message->setStyleSheet("font-size: 11pt;");
    message->setWordWrap(true);
    activeNodeHeader = new QLabel(this);
    activeNodeHeader->setGeometry(5, 290, 190, 60);
    activeNodeHeader->setStyleSheet("font-size: 12pt;");
    activeNodeHeader->setWordWrap(true);
    activeNodeHeader->setText("№ Активной вершины: ");
    activeNode = new QLineEdit(this);
    activeNode->setGeometry(135, 290, 60, 60);
    activeNode->setStyleSheet("font-size: 12pt;");
    goToSmallerActive = new QPushButton(this);
    goToSmallerActive->setGeometry(250, 560, 250, 60);
    goToSmallerActive->setStyleSheet("font-size: 12pt;");
    goToSmallerActive->setText("К меньшей вершине");
    goToBiggerActive = new QPushButton(this);
    goToBiggerActive->setGeometry(510, 560, 250, 60);
    goToBiggerActive->setStyleSheet("font-size: 12pt;");
    goToBiggerActive->setText("К большей вершине");
    pw = nullptr;
    connect(showGraph, &QPushButton::clicked, this, &Interface::updateGraph);
    connect(goToSmallerActive, &QPushButton::clicked, this, &Interface::smallerActive);
    connect(goToBiggerActive, &QPushButton::clicked, this, &Interface::biggerActive);
}

void Interface::setPaintingWidget(PaintingWidget *pw)
{
    this->pw = pw;
}

Interface::~Interface()
{
    delete showGraph;
    delete filePath;
    delete interfaceHeader;
    delete messageHeader;
    delete message;
    delete showGraphHeader;
}

void Interface::updateGraph() {
    QString pathToFile = filePath->text();
    int activeNodeNum = activeNode->text().toInt();
    if (!QFile::exists("values.txt")) {
        message->setText("Ошибка! Файл не найден!");
        return;
    }
    QFile file(pathToFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        message->setText("Ошибка! Не удалось прочитать файл!");
        return;
    }
    int n = 0;
    int m = 0;
    QVector<int> values;
    message->setText("Матрица смежности:\n");
    while (!file.atEnd()){
        QString line = file.readLine();
        QStringList strings = line.split(QRegularExpression("\\s+"), QString::SkipEmptyParts);
        if (strings.size() != m and m != 0) {
            message->setText("Ошибка! Неквадратная матрица смежности!");
            return;
        }
        if (m == 0)
            m = strings.size();
        for (int i = 0; i < strings.size(); i++) {
            values.append(strings[i].toInt());
            message->setText(message->text() + strings[i] + " ");
        }
        message->setText(message->text() + "\n");
        n++;
    }
    if (n != m) {
        message->setText("Ошибка! Неквадратная матрица смежности!");
        return;
    }
    if(activeNodeNum>m||activeNodeNum<1){
        message->setText("Ошибка! Неверный ввод номера активной вершины!");
        return;
    }
    pw->changeGraph(values, activeNodeNum);
}
void Interface::biggerActive() {
    pw->updateActive(1);
}
void Interface::smallerActive() {
    pw->updateActive(0);
}
