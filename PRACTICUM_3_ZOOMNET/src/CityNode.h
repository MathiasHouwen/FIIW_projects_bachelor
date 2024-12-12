//
// Created by ebbew on 12-12-2024.
//

#include <string>
#include <unordered_set>
#include "Connection.h"

#ifndef PRACTICUM_3_ZOOMNET_CITYNODE_H
#define PRACTICUM_3_ZOOMNET_CITYNODE_H

#endif //PRACTICUM_3_ZOOMNET_CITYNODE_H

struct CityNode{
    std::string cityName;
    std::unordered_set<Connection*> connections;
    explicit CityNode(std::string name) : cityName(name), connections(){};
};