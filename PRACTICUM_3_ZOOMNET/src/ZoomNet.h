//
// Created by houwe on 5/12/2024.
//

#ifndef PRACTICUM_3_ZOOMNET_ZOOMNET_H
#define PRACTICUM_3_ZOOMNET_ZOOMNET_H

#include <string>
#include "graph/Graph.h"
#include "ZoomNetGraph.h"

using namespace std;

class ZoomNet {
private:
    unordered_map<string, ZoomNetGraph*> graphs;

public:
    void designMST(string graphName);
    void adaptMST(string graphName);
    bool newConnectionBetter(const string& source, const string& destination, int weight, Graph *graph);
};


#endif //PRACTICUM_3_ZOOMNET_ZOOMNET_H
