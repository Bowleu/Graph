#ifndef GRAPH_H
#define GRAPH_H

#include "squareMatrix.h"

class Graph
{
    SquareMatrix<int> *m;
    int count;
public:
    Graph();
    Graph(QVector<int> values);
    int size();
    int element(int i, int j);
    ~Graph();
};

#endif // GRAPH_H
