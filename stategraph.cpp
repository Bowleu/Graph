#include "stategraph.h"

StateGraph::StateGraph() : Graph()
{
    active = 0;
}

StateGraph::StateGraph(QVector<int> values) : Graph(values)
{
    active = 0;
}
void StateGraph::setActive(int value){
    if(value > size()-1) active = 0;
    else if(value < 0) active = size()-1;
    else active = value;
}
int StateGraph::getActive(){
    return active;
}
