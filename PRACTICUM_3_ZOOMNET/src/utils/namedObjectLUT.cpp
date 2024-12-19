//
// Created by ebbew on 12-12-2024.
//

#include "namedObjectLUT.h"

using namespace std;

template<typename T>
void namedObjectLUT<T>::add(const string& name) {
    auto value = new T(name);
    lookupTable[name] = value;
}

template<typename T>
void namedObjectLUT<T>::remove(const string& name) {
    auto value = lookupTable[name];
    lookupTable.erase(name);
    delete value;
}

template<typename T>
T *namedObjectLUT<T>::peek(const string& name) const{
    if(!lookupTable.contains(name)) return nullptr;
    return lookupTable.at(name);
}

template<typename T>
bool namedObjectLUT<T>::contains(const string &name) {
    return peek(name);
}

template class namedObjectLUT<CityNode>;