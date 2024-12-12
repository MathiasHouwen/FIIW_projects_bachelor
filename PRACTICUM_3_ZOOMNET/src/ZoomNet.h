//
// Created by houwe on 5/12/2024.
//

#ifndef PRACTICUM_3_ZOOMNET_ZOOMNET_H
#define PRACTICUM_3_ZOOMNET_ZOOMNET_H

#include <string>
#include "Graph.h"

using namespace std;

class ZoomNet {
private:
    unordered_map<string, Graph*> graphs;

public:
    void designMST(string graphName);
    void adaptMST(string graphName);
};


#endif //PRACTICUM_3_ZOOMNET_ZOOMNET_H
