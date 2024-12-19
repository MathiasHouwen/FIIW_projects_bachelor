// taakverdeling en uitleg: zie h-file


#include "ZoomNetGraph.h"
using namespace std;

void ZoomNetGraph::generateMST(const unordered_set<Connection *> &excludeSet,
                               const unordered_set<Connection *> &includeSet) {

    /*
     * main logica: kijk voor elke connectie in de sorted connecties edge list of er een cyclus ontstaat
     * nee -> maak real, ja -> dan bestaat er al een minimaal pad tussen die cities
     * dat pad is minimaal omdat dit proces gebuert op de gesorteerde (by weight) edge list
     */


    // maak alle connections die ge-include moeten worden, real
    for (Connection* includedConnection : includeSet)
        includedConnection->realityCheck = true;

    // maak elke connectie real als er geen cyclus is (vorlgorde gebeuert doordat allConnectionsSorted sorted op weight is)
    for (Connection* connection : allConnectionsSorted) {
        unordered_set<CityNode*> visitedNodes;
        visitedNodes.insert(connection->cityNodes[0]);

        // skip als connection excluded is (insert visitednodes is wel op voorhand om iteraties te verminderen)
        if (excludeSet.contains(connection))
            continue;

        // als er geen cyclus bestaat, voeg toe
        bool cycle = checkCycle(connection->cityNodes[1], connection->cityNodes[0], visitedNodes);
        if (!cycle)
            connection->realityCheck = true;
    }
}

bool ZoomNetGraph::checkCycle(CityNode *currentNode, CityNode *prevNode, unordered_set<CityNode*> &visitedNodes) {

    /*
     * main logica: als je ooit een visited node terug vind dan heb je een cyclus ge-traversed
     */

    // als je een vorige node terug ziet, is er een cyclus
    if (visitedNodes.contains(currentNode))
        return true;

    // onthoud de huidige node
    visitedNodes.insert(currentNode);

    // alle adjacent nodes:
    for (auto connectionEntry : currentNode->connections) {
        auto nextCity = connectionEntry.first;
        auto connection = connectionEntry.second;

        // connecties die niet real zijn kunnen geskipt worden
        if (!connection->realityCheck)
            continue;

        // de eerste conditie voorkomt dat het algoritme oneindig op en neer zou gaan tussen twee connecties
        // ( en dat de direct vorige node dus ook niet meteen gezien wordt in visited nodes )
        // als check cycle ooit true is, kan die true door de hele return stack heen
        if (nextCity != prevNode && checkCycle(nextCity, currentNode, visitedNodes))
            return true;
    }
    // als er tot nu toe nog geen true gereturnt is, dan is er geen cyclus in de huidige (sub)-tree
    return false;
}

bool ZoomNetGraph::isNewConnectionBetter(const string& city1, const string& city2, int weight) {

    /*
     * main logica: vind de weight van het bestaande pad en vergelijk met de weight van de nieuwe connectie
     * heeft identiek resultaat aan connectie toevoegen en een cyclus zoeken en de goedkoopste helft kiezen
     */

    // vind de twee city nodes
    auto cityNode1 = cityNodesLookupTable.peek(city1);
    auto cityNode2 = cityNodesLookupTable.peek(city2);
    // edge case: nodes bestaan niet
    if(printErrorIfCityIsNull(cityNode1, cityNode2)) return false;

    // bereken de weight van het bestaande pad
    int oldWeight = getWeightOfPath(cityNode1, nullptr, cityNode2, 0);

    cout << "Old path weight of " << city1 << "-" << city2 << ": " << oldWeight << " vs new connection: " << weight << endl;

    // vergelijk met de nieuwe weight
    return weight <= oldWeight; // <= ipv < want nieuwe connection is maar 1 edge -> compactere 'mooiere' graph
}

int ZoomNetGraph::getWeightOfPath(CityNode *currentCity, CityNode* previousCity, CityNode *endCity, int totalWeight) {

    /*
     * main logica:
     *  - return een weight van -1 bij alle leaf nodes
     *  - als je van recursie -1 krijgt, blijf -1 doorgeven
     *  -> zo hebben alle subtrees die niet de end node bevatten -1 als 'ongeldige' weight
     *  - als je de end node ziet, return zijn weight
     *  - zolang je van recursie geen -1 krijgt, return die weight + current weight, tot aan de eerste call (= start node)
     *  -> uiteindelijk is dat de totale weight van het pad
     */

    // voor alle adjacent connecties, visit hun paths
    for(auto connectionEntry : currentCity->connections){
        auto otherCity = connectionEntry.first;
        auto connection = connectionEntry.second;

        // connecties die niet real zijn kunnen geskipt worden
        // terug komen naar parent kan ook geskipt worden
        if (!connection->realityCheck || otherCity == previousCity)
            continue;

        // als de te bezoeken city de eindbestemming is, hoef je niet meer te zoeken
        if(otherCity == endCity)
            return connection->weight;

        // als het pad niet -1 is, dan is dat het pad waar de weight van hier boven returned is
        int pathWeight = getWeightOfPath(otherCity, currentCity, endCity,totalWeight+1);
        if(pathWeight != -1)
            return connection->weight + pathWeight;
    }
    return -1;
}

// Genrate channcels for current networks
void ZoomNetGraph::generateChannels(CityNode *currCity, CityNode* previousCity, int channel) {

    /*
     * main logica: simpele traversal waarbij je channel als recursie parameter gebruikt
     * bij elke recursie call inverteer je de parameter ( tussen 0 en 1 )
     * (recursie call komt overeen met 'depth' als je de MST bekijkt als tree -> channel alterneert dus in het juiste patroon)
     */

    currCity->channel = channel;

    // voor alle connecties, visit hun paths
    for(auto connectionEntry : currCity->connections){
        auto nextCity = connectionEntry.first;
        auto connection = connectionEntry.second;

        // connecties die niet real zijn kunnen geskipt worden
        if (!connection->realityCheck || nextCity == previousCity)
            continue;

        generateChannels(nextCity, currCity, 1 - channel);
    }
}

void ZoomNetGraph::graphColouring(CityNode *currCity, CityNode* previousCity, unordered_set<CityNode*> &visitedNodes){

    /*
     * main logica:
     * TODO mathais, leg uit. Ik zie te veel loops om zin te hebben om deze code te lezen
     */
    visitedNodes.insert(currCity);

    // vind alle adjacent channels (enkel cities die al een channel hebben)
    unordered_set<int> adjacentChannels;
    for(auto connectionEntry : currCity->connections){
        auto nextCity = connectionEntry.first;

        // Als stad al een channel heeft voeg die toe
        if (nextCity->channel != -1){
            adjacentChannels.insert(nextCity->channel);
        }
    }

    // bepaal minimale channel die niet in de adjacent channels zit
    // ookal is de bovenste for loop groot, is adjacentChannels nooit groot
    // volgende while loop heeft dus geen grote impact op time complexity
    int channel = 0;
    while (adjacentChannels.contains(channel) || channel == currCity->channel){
        ++channel;
    }
    // dat wordt de huidige channel
    currCity->channel = channel;

    for(auto connectionEntry : currCity->connections){
        auto nextCity = connectionEntry.first;
        auto connection = connectionEntry.second;

        if (!connection->realityCheck)
            continue;

        if(!visitedNodes.contains(nextCity)){
            graphColouring(nextCity, currCity, visitedNodes);
        }
    }
}

void ZoomNetGraph::generateRealChannels() {
    Connection* fistConn = *allConnectionsSorted.begin();
    generateChannels(fistConn->cityNodes[0], nullptr, 0);
}

void ZoomNetGraph::generateALlPossibleChannels() {
    unordered_set<CityNode*> visitedNodes = {};
    Connection* fistConn = *allConnectionsSorted.begin();
    graphColouring(fistConn->cityNodes[0], nullptr, visitedNodes);
}
