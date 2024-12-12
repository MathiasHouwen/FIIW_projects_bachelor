//
// Created by ebbew on 12-12-2024.
//

#include "CityNodesLUT.h"

using namespace std;

void CityNodesLUT::add(const string& cityName) {
    auto city = new CityNode(cityName);
    lookupTable[cityName] = city;
}

void CityNodesLUT::remove(const string& cityName) {
    auto city = lookupTable[cityName];
    lookupTable.erase(cityName);
    delete city;
}

CityNode *CityNodesLUT::peek(const string& cityName) const{
    if(!lookupTable.contains(cityName)) return nullptr;
    return lookupTable.at(cityName);
}
