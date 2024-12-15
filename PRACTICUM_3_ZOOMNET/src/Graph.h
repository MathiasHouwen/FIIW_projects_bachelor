//
// Created by robin on 5/12/2024.
//

#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <unordered_map>
#include <iostream>
#include "Graph.h"
#include "GraphStructs.h"
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

    friend ostream &operator<<(ostream &os, const Graph &graph);


protected:
    set<Connection*, ConnectionPointerComparator> allConnectionsSorted;
    CityNodesLUT cityNodesLookupTable;

private:
    static bool printErrorIfCityIsNull(CityNode* city1, CityNode* city2);
    static void printWarningIfConnectionToggleHasNoEffect(bool real, const Connection *connection) ;
    static bool printErrorIfConnectionIsNotMutual(CityNode* city1, CityNode* city2);
    void printWarningIfConnectionExists(Connection* connection);

};



#endif //GRAPH_H
