// volledig gemaakt door Ebbe
// maar de structs bestonden al, door Robin
// Mathias heeft channel toegevoegd
// maar de structs zijn zwaar aangepast ( halve graph is basically refactored)

// deze structs zijn bewust gemaakt met hoge coupling met graph
// de LUT en graph handlen memory voor connection en citynode pointers

#include <string>
#include <utility>
#include <set>
#include <unordered_map>
#include <ostream>

#ifndef PRACTICUM_3_ZOOMNET_CITYNODE_H
#define PRACTICUM_3_ZOOMNET_CITYNODE_H

// forward declaration
struct Connection;

struct CityNode{
    ///@brief naam van de city
    const std::string& cityName{};
    /**
     * Adjacent connecites
     * Key = CityNode van de connectie
     * Value = connectie zelf
     * waarom map? -> O(1) connectie pointers terug vinden op basis van 2 cities
     */
    std::unordered_map<CityNode*, Connection*> connections{};
    ///@brief channel van de city
    int channel{-1};

    explicit CityNode(const std::string& name);
    friend std::ostream &operator<<(std::ostream &os, const CityNode &node);
};

struct Connection{
    ///@brief 2 city nodes waartussen de connectie
    CityNode* cityNodes[2] = {nullptr, nullptr};

    ///@brief weight van de connectie
    int weight{0};

    ///@brief connectie is real, of connectie is een niet-echt-verbonden possible connectie
    bool realityCheck{false};

    /**
     * Geeft de andere city van de 2, als er 1 gegeven is
     * @param node: de ene city
     * @return: de andere city
     */
    CityNode* other(CityNode* node) const;

    Connection(CityNode* cityNode1, CityNode* cityNode2, int weight);
    Connection() = default;

    friend std::ostream &operator<<(std::ostream &os, const Connection &connection);
    bool operator<(const Connection& other) const;
};

///@brief comparator voor city pointers, want pointers gebruiken niet de comparator van de struct
struct ConnectionPointerComparator{
    bool operator()(Connection* a, Connection* b) const;
};




#endif //PRACTICUM_3_ZOOMNET_CITYNODE_H
