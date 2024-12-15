//
// Created by ebbew on 15-12-2024.
//

#ifndef PRACTICUM_3_ZOOMNET_ZOOMNETGRAPH_H
#define PRACTICUM_3_ZOOMNET_ZOOMNETGRAPH_H


#include "Graph.h"

class ZoomNetGraph : public Graph{
public:
    void generateMST(const unordered_set<Connection *> &excludeSet = {}, const unordered_set<Connection *> &includeSet = {});
    //int findBiggestWeight(Connection* connection);

private:
    bool checkCycle(CityNode* currentNode, CityNode* prevNode, unordered_set<CityNode*> &visitedNodes);
    //bool isNewConnectionBetter(const Connection& connection);
    //int getWeightOfPath(CityNode* source, CityNode* destination);
};


#endif //PRACTICUM_3_ZOOMNET_ZOOMNETGRAPH_H
