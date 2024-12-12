//
// Created by ebbew on 12-12-2024.
//

#include <string>
#include <utility>
#include <set>

#ifndef PRACTICUM_3_ZOOMNET_CITYNODE_H
#define PRACTICUM_3_ZOOMNET_CITYNODE_H
struct Connection;
struct CityNode{
    std::string cityName{};
    std::set<Connection> connections{};

    explicit CityNode(std::string name);
    void connect(CityNode* otherCity, int weight);
    void disConnect(CityNode* otherCity, int weight);
};

struct Connection{
    CityNode* cityNode{nullptr};
    int weight{0};
    bool realityCheck{false};

    Connection(CityNode* cityNode, int weight);
    Connection() = default;

    bool operator<(const Connection& other) const;
};




#endif //PRACTICUM_3_ZOOMNET_CITYNODE_H
