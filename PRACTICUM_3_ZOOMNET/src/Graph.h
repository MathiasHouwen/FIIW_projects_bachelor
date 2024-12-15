//
// Created by robin on 5/12/2024.
//

#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <unordered_map>
#include <iostream>
#include "Graph.h"
#include "CityNode.h"
#include "CityNodesLUT.h"
#include <queue>
#include <limits>
#include <iostream>
#include <set>
#include <vector>
#include <unordered_set>

struct Connection;
using namespace std;

//struct ConnectionPointerComparator {
//  bool operator()(const Connection* lhs, const Connection* rhs) const {
//    return lhs->weight < rhs->weight;
//  }
//};

class Graph {
public:
    void addCity(const std::string& cityName);
    void removeCity(const std::string& cityName);
    void addConnection(const std::string &city1Name, const std::string &city2Name, int weight);
    void toggleConnection(const std::string &city1Name, const std::string &city2Name, bool real);

    void generateMST(const unordered_set<Connection *> &excludeSet = {}, const unordered_set<Connection *> &includeSet = {});
    //Connection* getConnection(const CityNode *source, const CityNode *destination) const;
    int findBiggestWeight(Connection* connection);

private:
    set<Connection*, ConnectionPointerComparator> allConnectionsSorted;
    CityNodesLUT cityNodesLookupTable;

    static bool printErrorIfCityIsNull(CityNode* city1, CityNode* city2);
    void printWarningIfConnectionExists(Connection* connection);
    static bool printErrorIfConnectionIsNotMutual(CityNode* city1, CityNode* city2);
    bool checkCycle(const CityNode* start, const CityNode* prevNode, unordered_set<string> &visitedNodes);
    static void printroute(const unordered_set<string> &visitedNodes, int distanceTraveled);
    bool isNewConnectionBetter(const Connection& connection);
    int getWeightOfPath(CityNode* source, CityNode* destination);

    static void printWarningIfConnectionToggleHasNoEffect(bool real, const Connection *connection) ;
};



#endif //GRAPH_H
