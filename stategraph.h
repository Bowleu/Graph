#ifndef STATEGRAPH_H
#define STATEGRAPH_H
#include "graph.h"

class StateGraph : public Graph
{
    int active = 0;
public:
    StateGraph();
    StateGraph(QVector<int> values);
    void setActive(int value);
    int getActive();
};

#endif // STATEGRAPH_H
