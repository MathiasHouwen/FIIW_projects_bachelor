//
// Created by ebbew on 15-12-2024.
//

#ifndef PRACTICUM_3_ZOOMNET_ZOOMNETGRAPH_H
#define PRACTICUM_3_ZOOMNET_ZOOMNETGRAPH_H


#include "Graph.h"

class ZoomNetGraph : public Graph{
public:
    void generateMST(const unordered_set<Connection *> &excludeSet = {}, const unordered_set<Connection *> &includeSet = {});
    bool isNewConnectionBetter(const string& city1, const string& city2, int weight);
    //int findBiggestWeight(Connection* connection);

private:
    bool checkCycle(CityNode* currentNode, CityNode* prevNode, unordered_set<CityNode*> &visitedNodes);
    int getWeightOfPath(CityNode* currentCity, CityNode* previousCity, CityNode* endCity, int totalWeight, unordered_set<CityNode*> &visitedNodes);
};


#endif //PRACTICUM_3_ZOOMNET_ZOOMNETGRAPH_H
