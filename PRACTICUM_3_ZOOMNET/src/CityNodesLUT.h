//
// Created by ebbew on 12-12-2024.
//

#ifndef PRACTICUM_3_ZOOMNET_CITYNODESLUT_H
#define PRACTICUM_3_ZOOMNET_CITYNODESLUT_H


#include <string>
#include "CityNode.h"
#include <unordered_map>

class CityNodesLUT {
private:
    std::unordered_map<std::string, CityNode*> lookupTable;
public:
    void add(const std::string& cityName);
    void remove(const std::string& cityName);
    CityNode* peek(const std::string& cityName) const;
};


#endif //PRACTICUM_3_ZOOMNET_CITYNODESLUT_H
