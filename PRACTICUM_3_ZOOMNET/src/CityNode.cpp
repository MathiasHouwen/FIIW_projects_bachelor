//
// Created by ebbew on 12-12-2024.
//

#include "CityNode.h"

/*
 * CITYNODE
 */
CityNode::CityNode(std::string name) : connections(), cityName(std::move(name)){}


void CityNode::connect(CityNode *otherCity, int weight){
    connections.insert({otherCity, weight});
}

void CityNode::disConnect(CityNode *otherCity, int weight) {
    connections.erase({otherCity, weight});
}

/*
 * CONNECTION
 */
Connection::Connection(CityNode *cityNode, int weight) : cityNode(cityNode), weight(weight) {}

bool Connection::operator<(const Connection &other) const {
    return weight < other.weight;
}
