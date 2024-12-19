// taakverdeling en uitleg: zie h-file


#include "ZoomNet.h"
using namespace std;

void ZoomNet::designMST(const std::string& graphName) {

    if (!graphs.contains(graphName)){

        auto graph = new ZoomNetGraph();

        graph->addCity("a");
        graph->addCity("b");
        graph->addCity("c");
        graph->addCity("d");
        graph->addCity("e");
        graph->addCity("f");

        graph->addConnection("a", "b", 11);
        graph->addConnection("a", "c", 10);
        graph->addConnection("a", "e", 13);
        graph->addConnection("b", "c", 15);
        graph->addConnection("b", "d", 9);
        graph->addConnection("b", "e", 7);
        graph->addConnection("b", "f", 21);
        graph->addConnection("c", "f", 8);
        graph->addConnection("d", "e", 12);
        graph->addConnection("f", "d", 18);

        graphs[graphName] = graph;
    }

    ZoomNetGraph *graph = graphs[graphName];
    graph->generateMST({}, {});
    cout << *graph << endl;

}

void ZoomNet::adaptMST(const std::string& graphName) {
    if (!graphs.contains(graphName)){
        designMST(graphName);
    }

    ZoomNetGraph *graph = graphs[graphName];
    graph->generateMST();
    // TODO geef include en exclude parameters mee
}

bool ZoomNet::newConnectionBetter(const std::string& graphName) {
    //TODO gebruik functie van ZoomNetGraph

    return false;
}
