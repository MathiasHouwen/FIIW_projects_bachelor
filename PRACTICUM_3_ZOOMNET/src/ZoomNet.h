// door mathias gemaakt
// zeer kleine aanpassing door ebbe in designMST

// main zoomnet class
// doel: hardcoded voorbeelden in een clean public interface

// lees ook /docs/discussion.md voor details, andere algoritmes en edge cases


#ifndef PRACTICUM_3_ZOOMNET_ZOOMNET_H
#define PRACTICUM_3_ZOOMNET_ZOOMNET_H

#include <string>
#include <unordered_map>
#include "graph/Graph.h"
#include "ZoomNetGraph.h"

class ZoomNet {
private:
    ///@brief map om meerdere voorbeeld-graphs te mappen op een voorbeeld-identifier-naam
    std::unordered_map<std::string, ZoomNetGraph*> graphs;


    void generateGraph(const std::string& graphName);

public:
    /**
     * Genereert een initieel netwerk
     * @param graphName: naam van voorbeeld
     */
    void designMST(const std::string& graphName);
    /**
     * Genereert het netwerk met included en excluded connecties
     * @param graphName: naam van voorbeeld
     */
    void adaptMST(const std::string& graphName);
    /**
     * kijkt of een nieuwe connectie beter is
     * @param graphName: naam van voorbeeld
     */
    bool newConnectionBetter(const std::string &graphName, const std::string &city1, const std::string &city2, int w);
    /**
     * generate channels voor current network
     * @param graphName: naam van voorbeeld
     */
    void generateChannels(const std::string &graphName);
    /**
     * generate channels voor volledig netwerk
     * @param graphName: naam van voorbeeld
     */
    void colourGraph(const std::string &graphName);
};


#endif //PRACTICUM_3_ZOOMNET_ZOOMNET_H
