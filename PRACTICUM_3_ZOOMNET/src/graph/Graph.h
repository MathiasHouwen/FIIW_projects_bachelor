// functies volledig gemaakt door Ebbe, datastructuur van edge list door Robin
// lees ook /docs/discussion.md voor details, andere algoritmes en edge cases

#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <unordered_map>
#include <iostream>
#include "Graph.h"
#include "GraphStructs.h"
#include "../utils/namedObjectLUT.h"
#include <queue>
#include <limits>
#include <iostream>
#include <set>
#include <vector>
#include <unordered_set>

class Graph {
public:
    /**
     * Maakt alle connecties terug niet-real en zet hun channels op -1
     */
    void clearConnections();
    /**
     * Voegt een nieuwe city toe aan de graph
     * @param cityName: naam van de nieuwe city (andere parameters zijn default in CityNode struct)
     */
    void addCity(const std::string& cityName);
    /**
     * verwijderd een city (+ bij adjacent cities de connecties hiernaar)
     * @param cityName: naam van de city
     */
    void removeCity(const std::string& cityName);
    /**
     * Voegt een connectie toe ( by default niet real )
     * @param city1Name: naam van eerste city
     * @param city2Name: naam van andere city
     * @param weight: weight van connectie
     */
    void addConnection(const std::string &city1Name, const std::string &city2Name, int weight);
    /**
     * Update de connectie om real of niet-real (possible) te zijn
     * @param city1Name: naam van eerste city
     * @param city2Name: naam van andere city
     * @param real: reality van de connectie
     */
    void toggleConnection(const std::string &city1Name, const std::string &city2Name, bool real);
    /**
     * Zoek de connectie pointer op basis van zijn twee cities
     * @param city1Name: naam van eerste city
     * @param city2Name: naam van andere city
     * @return: pointer naar de connectie
     * @tijdscomplexiteit: O(1)
     */
    Connection* getConnection(const std::string &city1Name, const std::string &city2Name);

    friend std::ostream &operator<<(std::ostream &os, const Graph &graph);


protected:
    ///@brief set van alle connecties (edge list), gesorteerd op weight (connection pointers worden hier gemanaged)
    std::set<Connection*, ConnectionPointerComparator> allConnectionsSorted;
    ///@brief Lookup table voor de city nodes (citynode pointers worden daar in gemanaged)
    namedObjectLUT<CityNode> cityNodesLookupTable;

    static bool printErrorIfCityIsNull(CityNode* city1, CityNode* city2);

private:
    static void printWarningIfConnectionToggleHasNoEffect(bool real, const Connection *connection) ;
    static bool printErrorIfConnectionIsNotMutual(CityNode* city1, CityNode* city2);
    void printWarningIfConnectionExists(Connection* connection);

};



#endif //GRAPH_H
