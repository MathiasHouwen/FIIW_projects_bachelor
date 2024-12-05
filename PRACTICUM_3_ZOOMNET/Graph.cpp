//
// Created by robin on 5/12/2024.
//

#include "Graph.h"

void Graph::addNode(CityNode *node) {
    nodes[node->city] = node;
}

void Graph::removeNode(CityNode *node) {
    if (nodes[node->city]) {
        nodes.erase(node->city);
    }
    else {
        cout << "City not found" << endl;
    }
}

void Graph::setConnection(CityNode *source, CityNode *destination, int connection) {
    if (source->connections[destination] && destination->connections[source]) {
        cout << "Connection already exists" << endl;
    }
    else {
        source->connections[destination] = connection;
        destination->connections[source] = connection;
    }
}

std::unordered_map<CityNode *, int> Graph::getConnections(string city) {
    return nodes[city]->connections;
}

void Graph::getShortestPath(CityNode *source, CityNode *destination) {
    unordered_set<string> visitedCities = {};
    visitCity(source, 0, destination, visitedCities);
}

void Graph::visitCity(CityNode* node, int distanceTraveled, CityNode* destination, unordered_set<string> &visitedCities) {
    if (node == destination && visitedCities.size() == nodes.size()) {
        printroute(visitedCities, distanceTraveled);
        return;
    }
    if (node == destination) {return;}

    visitedCities.insert(node->city);
    for (auto cityEntry : getConnections(node->city)) {
        CityNode *cityNode = cityEntry.first;
        int distance = cityEntry.second;

        if (visitedCities.contains(cityNode->city)){return;}
        visitCity(cityNode, distanceTraveled + distance, destination, visitedCities, routes);
    }
}

void Graph::printroute(unordered_set<string> &visitedNodes, int distanceTraveled) {
    cout << "Route: " << endl;
    for(string city : visitedNodes) {
        cout << city << " ";
    }
    cout << endl << "Distance: " << distanceTraveled << endl;
}

