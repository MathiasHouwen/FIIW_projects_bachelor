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

bool ZoomNetGraph::isNewConnectionBetter(const string& city1, const string& city2, int weight) {
    auto cityNode1 = cityNodesLookupTable.peek(city1);
    auto cityNode2 = cityNodesLookupTable.peek(city2);
    if(printErrorIfCityIsNull(cityNode1, cityNode2)) return false;

    unordered_set<CityNode*> visitedNodes = {};
    int oldWeight = getWeightOfPath(cityNode1, nullptr, cityNode2, 0, visitedNodes);
    cout << "Old path weight of " << city1 << "-" << city2 << ": " << oldWeight << " vs new connection: " << weight << endl;
    return weight <= oldWeight; // <= ipv < want nieuwe connection is maar 1 edge -> compactere 'mooiere' graph
}

int ZoomNetGraph::getWeightOfPath(CityNode *currentCity, CityNode* previousCity, CityNode *endCity, int totalWeight, unordered_set<CityNode*> &visitedNodes) {

    visitedNodes.insert(currentCity);

    // voor alle connecties, visit hun paths
    for(auto connectionEntry : currentCity->connections){
        auto otherCity = connectionEntry.first;
        auto connection = connectionEntry.second;

        // connecties die niet real zijn kunnen geskipt worden
        // terug komen naar parent kan ook geskipt worden
        if (!connection->realityCheck || otherCity == previousCity)
            continue;

        // als de te bezoeken city de eindbestemming is, hoef je niet meer te zoeken
        if(otherCity == endCity)
            return connection->weight;

        // als het pad niet -1 is, dan is dat het pad waar de weight van hier boven returned is
        int pathWeight = getWeightOfPath(otherCity, currentCity, endCity,totalWeight+1, visitedNodes);
        if(pathWeight != -1)
            return connection->weight + pathWeight;
    }
    return -1;
}

// Genrate channcels for current networks
void ZoomNetGraph::generateChannels(CityNode *currCity, unordered_set<CityNode*> &visitedNodes, int channel) {

    visitedNodes.insert(currCity);

    // voor alle connecties, visit hun paths
    for(auto connectionEntry : currCity->connections){
        auto nextCity = connectionEntry.first;
        auto connection = connectionEntry.second;

        // connecties die niet real zijn kunnen geskipt worden
        if (!connection->realityCheck)
            continue;

        currCity->channel = channel;

        generateChannels(nextCity, visitedNodes, 1 - channel);
    }
}

void ZoomNetGraph::graphColouring(CityNode *currCity, unordered_set<CityNode*> &visitedNodes){

    visitedNodes.insert(currCity);
    unordered_set<int> adjacentChannels;

    for(auto connectionEntry : currCity->connections){
        auto nextCity = connectionEntry.first;
        auto connection = connectionEntry.second;

        if (!connection->realityCheck)
            continue;

        // Als stad al een channel heeft voeg die toe
        if (visitedNodes.contains(nextCity) && nextCity->channel != -1){
            adjacentChannels.insert(nextCity->channel);
        }
    }

    // gaat door all adjecents channels
    int channel = 0;
    while (adjacentChannels.contains(channel)){
        ++channel;
    }
    currCity->channel = channel;

    for(auto connectionEntry : currCity->connections){
        auto nextCity = connectionEntry.first;
        auto connection = connectionEntry.second;

        if (!connection->realityCheck)
            continue;

        if(!visitedNodes.contains(nextCity)){
            graphColouring(nextCity, visitedNodes);
        }
    }
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

//int Graph::getWeightOfPath(CityNode *source, CityNode *destination) {
//    for(auto connection : source->connections){
//        CityNode* destNode = connection->destination == currentNode ? connection->start : connection->destination;
//    }
//    return 0;
//}