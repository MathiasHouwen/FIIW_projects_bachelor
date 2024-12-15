//
// Created by ebbew on 12-12-2024.
//

#include <string>
#include <utility>
#include <set>
#include <unordered_map>
#include <ostream>

#ifndef PRACTICUM_3_ZOOMNET_CITYNODE_H
#define PRACTICUM_3_ZOOMNET_CITYNODE_H
struct Connection;
struct CityNode{
    const std::string& cityName{};
    std::unordered_map<CityNode*, Connection*> connections{};
    explicit CityNode(const std::string& name);

    friend std::ostream &operator<<(std::ostream &os, const CityNode &node);
};

struct Connection{
    CityNode* cityNodes[2] = {nullptr, nullptr};
    int weight{0};
    bool realityCheck{false};

    CityNode* other(CityNode* node) const;

    Connection(CityNode* cityNode1, CityNode* cityNode2, int weight);
    Connection() = default;

    friend std::ostream &operator<<(std::ostream &os, const Connection &connection);

    bool operator<(const Connection& other) const;
};

struct ConnectionPointerComparator{
    bool operator()(Connection* a, Connection* b) const;
};




#endif //PRACTICUM_3_ZOOMNET_CITYNODE_H
