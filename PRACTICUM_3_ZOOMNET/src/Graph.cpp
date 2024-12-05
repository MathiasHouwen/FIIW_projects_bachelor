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

void Graph::minimumSpanningTree(CityNode* start) {
    // Priority queue to get the edge with the smallest weight
    priority_queue<Edge, vector<Edge>, greater<>> edgeQueue;

    // Set of visited nodes
    unordered_set<string> visited;

    // Total weight of the MST
    int totalWeight = 0;

    // Add all edges of the starting node to the priority queue
    for (auto& connection : start->connections) {
        edgeQueue.push({start, connection.first, connection.second});
    }
    visited.insert(start->city);

    cout << "Edges in the Minimum Spanning Tree:" << endl;

    while (!edgeQueue.empty()) {
        // Get the smallest edge
        Edge currentEdge = edgeQueue.top();
        edgeQueue.pop();

        if (visited.find(currentEdge.destination->city) != visited.end()) {
            continue;
        }

        visited.insert(currentEdge.destination->city);

        totalWeight += currentEdge.weight;

        cout << currentEdge.source->city << " --(" << currentEdge.weight << ")--> " << currentEdge.destination->city << endl;

        for (auto& connection : currentEdge.destination->connections) {
            if (visited.find(connection.first->city) == visited.end()) {
                edgeQueue.push({currentEdge.destination, connection.first, connection.second});
            }
        }
    }

    cout << "Total Weight of the Minimum Spanning Tree: " << totalWeight << endl;
}

CityNode* Graph::getNode(const string& city) {
    if (nodes.find(city) != nodes.end()) {
        return nodes[city];
    } else {
        cout << "City not found" << endl;
        return nullptr;
    }
}