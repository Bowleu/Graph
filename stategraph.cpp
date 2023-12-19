#include "stategraph.h"

StateGraph::StateGraph() : Graph()
{
    active = 0;
}

StateGraph::StateGraph(QVector<int> values) : Graph(values)
{
    active = 0;
}
int StateGraph::findAdjVert(bool value){
    int newVert = -1;
    for(int j = 0;j<size();j++){
        qDebug() << element(active,j);
    }
    if(value){ // bigger vert
        for(int j = 0;j<size();j++){
            if (j==active) continue;
            if(element(active,j)>0){
                newVert = j;
            }
        }
    } else{
        for(int j = 0;j<size();j++){
            if (j==active) continue;
            if(element(active,j)>0){
                newVert = j;
                qDebug() << "1" << newVert;
                break;
                qDebug() << "2";
            }
        }
    }
    return newVert;
}
void StateGraph::setActive(int value){
    active = value;
}
int StateGraph::getActive(){
    return active;
}
