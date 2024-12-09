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
    if (source->connections.contains({source, destination, connection})) {
        cout << "Connection already exists" << endl;
    }
    else {
        auto* newConnection = new Connection({source, destination, connection});
        allConnections.insert(newConnection);
        source->connections.insert(*newConnection);
        destination->connections.insert(*newConnection);
    }
}

std::set<Connection> Graph::getConnections(string city) {
    return nodes[city]->connections;
}

CityNode* Graph::getNode(string city) {
    return nodes[city];
}

void Graph::getShortestPath() {
    unordered_set<string> visitedCities = {};
    visitCity(0, visitedCities);
}

void Graph::visitCity(int distanceTraveled, unordered_set<string> &visitedCities) {
    if (visitedCities.size() == nodes.size()-1) {
        printroute(visitedCities, distanceTraveled);
        return;
    }

    for (Connection* connection : allConnections) {
        unordered_set<string> visitedNodes;
        visitedNodes.insert(connection->start->city);
        if (checkCycle(connection->destination, visitedNodes)) {
            connection->realityCheck = true;
            cout << "Connection: " << connection->start->city << "->" << connection->destination->city << endl;
            distanceTraveled += connection->weight;
        }
    }
}

void Graph::printroute(unordered_set<string> &visitedNodes, int distanceTraveled) {
    cout << "Route: " << endl;
    for(const string& city : visitedNodes) {
        cout << city << " ";
    }
    cout << endl << "Distance: " << distanceTraveled << endl;
}

bool Graph::checkCycle(CityNode* currentNode, unordered_set<string> &visitedNodes) {
    visitedNodes.insert(currentNode->city);
    for (const Connection& connection : currentNode->connections) {
        CityNode* nextCity = connection.destination == currentNode ? connection.start : connection.destination;
        if (connection.realityCheck && visitedNodes.contains(nextCity->city)) {
            return true;
        }
        const bool finalDestination = checkCycle(nextCity, visitedNodes);
        if (finalDestination) {
            return finalDestination;    // Guard Clause
        }
    }
    return false;
}