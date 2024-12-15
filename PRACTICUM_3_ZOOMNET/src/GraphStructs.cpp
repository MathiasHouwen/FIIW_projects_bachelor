//
// Created by ebbew on 12-12-2024.
//

#include "GraphStructs.h"

/*
 * CITYNODE
 */
CityNode::CityNode(const std::string& name) : connections(), cityName(name){}

std::ostream &operator<<(std::ostream &os, const CityNode &node) {
    os << node.cityName;
    return os;
}

/*
 * CONNECTION
 */
Connection::Connection(CityNode* cityNode1, CityNode* cityNode2, int weight) : weight(weight), cityNodes(cityNode1, cityNode2) {}

bool Connection::operator<(const Connection &other) const {
    return weight < other.weight;
}

CityNode *Connection::other(CityNode *node) const {
    if(node == cityNodes[0]) return cityNodes[1];
    if(node == cityNodes[1]) return cityNodes[0];
    return nullptr;
}

std::ostream &operator<<(std::ostream &os, const Connection &connection) {
    os << "{ " << *connection.cityNodes[0] << "-" << *connection.cityNodes[0];
    os << " | " << connection.weight << " - " << (connection.realityCheck ? "real" : "open") << " }";
    return os;
}

bool ConnectionPointerComparator::operator()(Connection *a, Connection *b) const {
    return *a < *b;
}
