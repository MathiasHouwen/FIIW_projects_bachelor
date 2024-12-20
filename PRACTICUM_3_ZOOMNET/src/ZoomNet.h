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

//    ZoomNetGraph graph;

public:

//    ZoomNet();

    /**
     * Genereert een initieel netwerk
     * @param graphName: naam van voorbeeld
     */
    void designMST();
    /**
     * Genereert het netwerk met included en excluded connecties
     * @param graphName: naam van voorbeeld
     */
    void adaptMST();
    /**
     * kijkt of een nieuwe connectie beter is
     * @param graphName: naam van voorbeeld
     */
    bool newConnectionBetter(const std::string &city1, const std::string &city2, int w);
    /**
     * generate channels voor current network
     * @param graphName: naam van voorbeeld
     */
    void generateChannels();
    /**
     * generate channels voor volledig netwerk
     * @param graphName: naam van voorbeeld
     */
    void colourGraph();
};


#endif //PRACTICUM_3_ZOOMNET_ZOOMNET_H
