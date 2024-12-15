//
// Created by ebbew on 15-12-2024.
//

#include "ZoomNetGraph.h"

void ZoomNetGraph::generateMST(const unordered_set<Connection *> &excludeSet,
                               const unordered_set<Connection *> &includeSet) {
    // maak alle connections die ge-include moeten worden, real
    for (Connection* includedConnection : includeSet)
        includedConnection->realityCheck = true;

    // maak elke connectie real als er geen cyclus is (vorlgorde gebeuert doordat allConnectionsSorted sorted op weight is)
    for (Connection* connection : allConnectionsSorted) {
        unordered_set<CityNode*> visitedNodes;
        visitedNodes.insert(connection->cityNodes[0]);

        // skip als connection excluded is (insert visitednodes is wel op voorhand om iteraties te verminderen)
        if (excludeSet.contains(connection))
            continue;

        // als er geen cyclus bestaat, voeg toe
        bool cycle = checkCycle(connection->cityNodes[1], connection->cityNodes[0], visitedNodes);
        if (!cycle)
            connection->realityCheck = true;
    }
}

bool ZoomNetGraph::checkCycle(CityNode *currentNode, CityNode *prevNode, unordered_set<CityNode*> &visitedNodes) {
    // als je een vorige node terug ziet, is er een cyclus
    if (visitedNodes.contains(currentNode))
        return true;

    visitedNodes.insert(currentNode);

    for (auto connectionEntry : currentNode->connections) {
        auto nextCity = connectionEntry.first;
        auto connection = connectionEntry.second;
        // connecties die niet real zijn kunnen geskipt worden
        if (!connection->realityCheck)
            continue;

        if (nextCity != prevNode && checkCycle(nextCity, currentNode, visitedNodes))
            return true;
    }
    return false;
}

//int Graph::findBiggestWeight(Connection *connection) {
//    unordered_set<Connection*> cycle = findCycle(connection);
//    int biggestWeight = 0;
//    for (const Connection* connectionInCycle : cycle) {
//        if (connectionInCycle->weight > biggestWeight) {
//            biggestWeight = connectionInCycle->weight;
//        }
//    }
//return biggestWeight;
//}

//bool Graph::isNewConnectionBetter(const Connection &connection) {
//    int newWeight = connection.weight;
//    int oldWeight = getWeightOfPath(connection.start, connection.destination);
//    newWeight < oldWeight;
//}

//int Graph::getWeightOfPath(CityNode *source, CityNode *destination) {
//    for(auto connection : source->connections){
//        CityNode* destNode = connection->destination == currentNode ? connection->start : connection->destination;
//    }
//    return 0;
//}