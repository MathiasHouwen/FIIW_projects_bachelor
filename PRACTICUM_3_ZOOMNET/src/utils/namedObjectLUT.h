// volledig gemaakt door Ebbe

// Lookup table om pointers van objecten met een naam veilig op te slaan
// gebruikt voor CityNodes
// de class zal dus (bvb met CityNode)
// - een CityNode pointer aanmaken via city naam
// - een CityNode pointer opvragen via city naam
// - een CityNode pointer deleten via city naam

// Type T wordt verondersteld als een class/struct met een string naam, en een constructor die enkel een naam vraagt

#ifndef PRACTICUM_3_ZOOMNET_NAMEDOBJECTLUT_H
#define PRACTICUM_3_ZOOMNET_NAMEDOBJECTLUT_H


#include <string>
#include "../graph/GraphStructs.h"
#include <unordered_map>

/**
 * Lookup table voor named objects
 * @tparam T: type met een name string field en een constructor: T(string name)
 * @spaceComlexiteit O(N): voor elk object pointer is er ook een string in de map (keys worden ook opgeslagen in hashmaps)
 */
template<typename T>
class namedObjectLUT {
private:
    /// @brief lookup table: mapt de naam string naar een pointer van T
    std::unordered_map<std::string, T*> lookupTable;
public:
    /**
     * Maakt een nieuw object aan via naam
     * @param name naam van het object
     * @tijdscomplexiteit O(1)
     */
    void add(const std::string& name);
    /**
     * verwijderd een object via naam
     * @param name naam van het object
     * @tijdscomplexiteit O(1)
     */
    void remove(const std::string& name);
    /**
     * vraagt de object pointer op via naam
     * @param name naam van het object
     * @return pointer naar het object (null als niet gevonden)
     * @tijdscomplexiteit O(1)
     */
    T* peek(const std::string& name) const;
    /**
     * kijkt of een object bestaat met een naam
     * @param name naam van het object
     * @return boolean of het object bestaat
     * @tijdscomplexiteit O(1)
     */
    bool contains(const std::string& name);
};


#endif //PRACTICUM_3_ZOOMNET_NAMEDOBJECTLUT_H
