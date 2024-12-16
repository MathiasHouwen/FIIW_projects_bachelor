//
// Created by robin on 5/12/2024.
//

#include "Graph.h"

void Graph::addCity(const string &cityName) {
    // voeg city toe aan LUT (lut maakt zelf CityNode pointer)
    if(cityNodesLookupTable.contains(cityName))
        cerr << "WARNING: Trying add city: " << cityName << "to lookupTable, which already exists";
    cityNodesLookupTable.add(cityName);
}

void Graph::addConnection(const std::string &city1Name, const std::string &city2Name, int weight) {
    // zoek de 2 city pointers
    auto city1 = cityNodesLookupTable.peek(city1Name);
    auto city2 = cityNodesLookupTable.peek(city2Name);
    if(printErrorIfCityIsNull(city1, city2)) return;

    // maak connection
    auto connection = new Connection(city1, city2, weight);
    printWarningIfConnectionExists(connection);

    // connecteer elkaar
    allConnectionsSorted.insert(connection);
    city1->connections[city2] = connection;
    city2->connections[city1] = connection;
}

void Graph::removeCity(const string &cityName) {
    // zoek de pointer van de city
    auto city = cityNodesLookupTable.peek(cityName);

    // van al zijn connecties: verwijder de connectie met deze city
    for(auto connectionEntry : city->connections){
        auto otherCity = connectionEntry.first;
        auto connection = connectionEntry.second;
        otherCity->connections.erase(city);
        delete connection;
    }

    // verwijder deze city volledig
    cityNodesLookupTable.remove(cityName);
}

void Graph::toggleConnection(const string &city1Name, const string &city2Name, bool real) {
    // zoek de 2 city pointers
    auto city1 = cityNodesLookupTable.peek(city1Name);
    auto city2 = cityNodesLookupTable.peek(city2Name);
    if (printErrorIfCityIsNull(city1, city2)) return;
    if (printErrorIfConnectionIsNotMutual(city1, city2)) return;

    // maak connectie real
    auto connection = city1->connections[city2];
    printWarningIfConnectionToggleHasNoEffect(real, connection);
    connection->realityCheck = real;
}

Connection *Graph::getConnection(const string &city1Name, const string &city2Name) {
    // zoek de 2 city pointers
    auto city1 = cityNodesLookupTable.peek(city1Name);
    auto city2 = cityNodesLookupTable.peek(city2Name);
    if (printErrorIfCityIsNull(city1, city2)) return nullptr;
    if (printErrorIfConnectionIsNotMutual(city1, city2)) return nullptr;

    auto connection = city1->connections[city2];
    return connection;
}

bool Graph::printErrorIfCityIsNull(CityNode *city1, CityNode *city2) {
    if(city1 == nullptr || city2 == nullptr){
        cerr << "ERROR: Trying to connect two cities but one is null: ";
        if(city1) cerr << *city1; else cerr << "null";
        cerr << " + ";
        if(city2) cerr << *city2; else cerr << "null" << endl;
        return true;
    }
    return false;
}

void Graph::printWarningIfConnectionExists(Connection *connection) {
    if(allConnectionsSorted.contains(connection))
        cerr << "WARNING: Trying to add connection" << *connection << "which already exists" << endl;

    auto city1 = connection->cityNodes[0];
    auto city2 = connection->cityNodes[1];

    if(city1->connections.contains(city2) && city1->connections[city2] == connection)
        cerr << "WARNING: Trying to add connection: " << *connection << " to city: " << *connection->cityNodes[0] << "which already has it: " << endl;
    if(city2->connections.contains(city1) && city2->connections[city1] == connection)
        cerr << "WARNING: Trying to add connection: " << *connection << " to city: " << *connection->cityNodes[1] << "which already has it: " << endl;

}

bool Graph::printErrorIfConnectionIsNotMutual(CityNode *city1, CityNode *city2) {
    if(!city1->connections.contains(city2))
        cerr << "ERROR: Trying to get connection which does not exist with " << *city2 << "on " << *city1 << endl;
    else if(!city2->connections.contains(city1))
        cerr << "ERROR: Trying to get connection which does not exist with " << *city1 << "on " << *city2 << endl;
    else if(city1->connections[city2] != city2->connections[city1])
        cerr << "ERROR: Connection between " << *city1 << " - " << *city2 << " is not mutually identical";
    else return false;
    return true;
}

void Graph::printWarningIfConnectionToggleHasNoEffect(bool real, const Connection *connection) {
    if(connection->realityCheck == real)
        cerr << "WARNING: Trying to toggle connection: " << *connection << " to " << (real ? "real" : "open") << " but it already is.";
}

ostream &operator<<(ostream &os, const Graph &graph) {
    for(auto connection : graph.allConnectionsSorted){
        os << *connection << endl;
    }
    return os;
}

void Graph::clearConnections() {
    for(auto connection : allConnectionsSorted)
        connection->realityCheck = false;
}


