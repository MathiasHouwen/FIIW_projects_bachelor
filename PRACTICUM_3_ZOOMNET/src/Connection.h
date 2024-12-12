//
// Created by ebbew on 12-12-2024.
//

#include "CityNode.h"

#ifndef PRACTICUM_3_ZOOMNET_CONNECTION_H
#define PRACTICUM_3_ZOOMNET_CONNECTION_H

#endif //PRACTICUM_3_ZOOMNET_CONNECTION_H

struct Connection{
    CityNode* cityNode{nullptr};
    int weight{0};
    bool realityCheck{false};
    bool operator<(const Connection& other) const;
};

bool Connection::operator<(const Connection &other) const {
        return weight < other.weight;
}
