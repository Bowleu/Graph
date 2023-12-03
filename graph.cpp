#include "graph.h"
#include <QtMath>

Graph::Graph()
{
    m = new SquareMatrix<int>(0);
    count = 0;
}

Graph::Graph(QVector<int> values) {
    count = qSqrt(values.size());
    m = new SquareMatrix<int>(count);
    for (int i = 0; i < values.size(); i++) {
        (*m)[i] = values[i];
    }
}

int Graph::element(int i, int j) {
    return (*m)[i * m->size() + j];
}

int Graph::size() {
    return count;
}

Graph::~Graph() {
    //delete m;
}
