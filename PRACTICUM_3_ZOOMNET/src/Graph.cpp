//
// Created by robin on 5/12/2024.
//

#include "Graph.h"

void Graph::addNode(CityNode *node) {
    nodes[node->city] = node;
}

void Graph::removeNode(const CityNode *node) {
    if (nodes[node->city]) {
        nodes.erase(node->city);
    }
    else {
        cout << "City not found" << endl;
    }
}

void Graph::setConnection(CityNode *source, CityNode *destination, int connection) {
    auto* newConnection = new Connection({source, destination, connection});
    if (source->connections.contains(newConnection)) {
        cout << "Connection already exists" << endl;
    }
    else {
        allConnections.insert(newConnection);
        source->connections.insert(newConnection);
        destination->connections.insert(newConnection);
    }
}

Connection* Graph::getConnection(const CityNode *source, const CityNode *destination) const {
    for (Connection *connection : allConnections) {
        if (connection->start == source && connection->destination == destination) {
            return connection;
        }
    }
    return nullptr;
}

std::set<Connection*> Graph::getConnections(const string& city) {
    return nodes[city]->connections;
}

CityNode* Graph::getNode(const string& city) {
    return nodes[city];
}

void Graph::generateMST(const unordered_set<Connection*>& excludeSet, const unordered_set<Connection*>& includeSet) {
    int distanceTraveled = 0;

    for (Connection* include : includeSet){
        include->realityCheck = true;
    }

    for (Connection* connection : allConnections) {
        unordered_set<string> visitedNodes;
        visitedNodes.insert(connection->start->city);

        if (excludeSet.contains(connection)) {
            continue;
        }

        if (!checkCycle(connection->destination, connection->start, visitedNodes)) {
            connection->realityCheck = true;
            cout << "Connection: " << connection->start->city << "->" << connection->destination->city << endl;
            distanceTraveled += connection->weight;
        }
    }
    cout << "Distance: " << distanceTraveled << endl;
}

void Graph::printroute(const unordered_set<string> &visitedNodes, const int distanceTraveled) {
    cout << "Route: " << endl;
    for(const string& city : visitedNodes) {
        cout << city << " ";
    }
    cout << endl << "Distance: " << distanceTraveled << endl;
}

bool Graph::checkCycle(const CityNode* currentNode, const CityNode* prevNode, unordered_set<string> &visitedNodes) {
    if (visitedNodes.contains(currentNode->city)){return true;}
    visitedNodes.insert(currentNode->city);
    for (const Connection* connection : currentNode->connections) {
        if (!connection->realityCheck) {
            continue;
        }
        CityNode* nextCity = connection->destination == currentNode ? connection->start : connection->destination;
        if (nextCity != prevNode && checkCycle(nextCity, currentNode, visitedNodes)) {return true;}
    }
    return false;
}