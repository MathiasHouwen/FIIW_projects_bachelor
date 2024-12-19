// door iedereen gemaakt, zie @author documentaties

// doel: erving van Graph:
// - graph = basis datastructuur, focus op add/remove/update/..
// - deze = specifieke algoritmes voor zoomnet

// lees ook /docs/discussion.md voor details, andere algoritmes en edge cases


#ifndef PRACTICUM_3_ZOOMNET_ZOOMNETGRAPH_H
#define PRACTICUM_3_ZOOMNET_ZOOMNETGRAPH_H


#include "graph/Graph.h"

class ZoomNetGraph : public Graph{
public:
    /**
     * Genereert een MST (op voorwaarde dat alle graph connecties op voorhand niet real zijn)
     * @param excludeSet: connecties die er niet real mogen worden
     * @param includeSet: connecites die er verplicht real moeten worden
     * @author Robin
     */
    void generateMST(const std::unordered_set<Connection *> &excludeSet = {}, const std::unordered_set<Connection *> &includeSet = {});
    /**
     * Kijkt of een nieuwe connectie de graph kan verbeteren
     * @param city1: eerste city van de connectie
     * @param city2: tweede city van de connectie
     * @param weight: weight van de connectie
     * @return: boolean of de connectie beter is
     * @author: Ebbe
     */
    bool isNewConnectionBetter(const std::string& city1, const std::string& city2, int weight);
    /**
     * Genereert channels voor alle cities, op basis van enkel real connecties
     * voorwaarde: er moet al een MST bestaan en alle channels moeten initieel -1 zijn
     * @author: Mathias, idee door Ebbe
     */
    void generateRealChannels();
    /** Genereert channels voor alle cities, op basis van alle possible connecties
     * voorwaarde: alle channels moeten initieel -1 zijn
     * @author: Mathias, debug hulp door Ebbe
     */
    void generateALlPossibleChannels();

private:
    /**
     * recursieve functie, kijkt of er een cyclus is (gebruikt door generateMST: een MST mag nooit een cyclus hebben)
     * @param currentNode: huidige city
     * @param prevNode: vorige city
     * @param visitedNodes: map voor memoisatie
     * @return: boolean of er een cyclus is
     * @author: Mathias
     */
    bool checkCycle(CityNode* currentNode, CityNode* prevNode, std::unordered_set<CityNode*> &visitedNodes);
    /**
     * recursieve functie: berekend de totale weight van het pad (er is maar 1 pad in een MST) tussen twee cities
     * @param currentCity: huidige city ( = in begin de start city)
     * @param previousCity: vorige city
     * @param endCity: eind city ( zoek pad tussen start city en eind city)
     * @param totalWeight: totale weight van het pad tussen de twee cities
     * @param visitedNodes: map voor memoisatie
     * @return: totale weight van het pad
     * @author: Ebbe
     */
    int getWeightOfPath(CityNode* currentCity, CityNode* previousCity, CityNode* endCity, int totalWeights);
    /**
     * recursieve helper functie voor de logica achter generateRealChannels:
     * In een MST hoeven er maar 2 channels te bestaan.
     * de functie alterneert dus tussen channel 0 en 1 op elke depth
     * @param currCity : huidige city
     * @param previousCity : vorige city
     * @param visitedNodes : map voor memoisatie
     * @param channel: channel (0 of 1)
     */
    void generateChannels(CityNode *currCity, CityNode* previousCity, int channel);
    /**
     * recursieve helper functie voor de logica achter generateALlPossibleChannels
     * coloring algoritme (op eigen verstand want literatuur was te wiskundig/complex)
     * @param currCity : huidige city
     * @param previousCity : vorige city
     * @param visitedNodes : map voor memoisatie
     */
    void graphColouring(CityNode *currCity, CityNode* previousCity, std::unordered_set<CityNode *> &visitedNodes);
};


#endif //PRACTICUM_3_ZOOMNET_ZOOMNETGRAPH_H
