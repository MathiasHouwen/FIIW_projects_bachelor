//
// Created by ebbew on 12-12-2024.
//

#ifndef PRACTICUM_3_ZOOMNET_NAMEDOBJECTLUT_H
#define PRACTICUM_3_ZOOMNET_NAMEDOBJECTLUT_H


#include <string>
#include "../graph/GraphStructs.h"
#include <unordered_map>

template<typename T>
class namedObjectLUT {
private:
    std::unordered_map<std::string, T*> lookupTable;
public:
    void add(const std::string& name);
    void remove(const std::string& name);
    T* peek(const std::string& name) const;
    bool contains(const std::string& name);
};


#endif //PRACTICUM_3_ZOOMNET_NAMEDOBJECTLUT_H
