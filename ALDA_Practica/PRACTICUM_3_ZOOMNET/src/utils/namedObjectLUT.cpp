// taakverdeling en uitleg: zie h-file


#include "namedObjectLUT.h"

using namespace std;

template<typename T>
void namedObjectLUT<T>::add(const string& name) {
    // maak nieuw object aan
    // T is verondersteld als een object met constructor die enkel een naam vraagt
    auto value = new T(name);
    // voeg toe aan table [O(1)]
    lookupTable[name] = value;
}

template<typename T>
void namedObjectLUT<T>::remove(const string& name) {
    // haal pointer uit table [O(1)]
    auto value = lookupTable[name];
    // verwijder object uit table [O(1)]
    lookupTable.erase(name);
    // verwijder object van heap
    delete value;
    // null checken hoef niet, want table.erase werkt via de name, en delete heeft geen effect bij nullpointers
}

template<typename T>
T *namedObjectLUT<T>::peek(const string& name) const{
    // edge case: object bestaat niet -> geef nullpointer [O(1)]
    if(!lookupTable.contains(name)) return nullptr;
    // anders, zoek object in lookup table [O(1)]
    return lookupTable.at(name);
}

template<typename T>
bool namedObjectLUT<T>::contains(const string &name) {
    // peek geeft een nullpointer als het object niet bestaat [O(1)]
    return peek(name) != nullptr;
}

template class namedObjectLUT<CityNode>;