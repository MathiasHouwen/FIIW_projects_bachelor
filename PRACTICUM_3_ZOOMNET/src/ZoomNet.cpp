//
// Created by houwe on 5/12/2024.
//

#include "ZoomNet.h"

void ZoomNet::designMST(string graphName) {

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

void ZoomNet::adaptMST(string graphName) {
    if (!graphs.contains(graphName)){
        designMST(graphName);
    }

    ZoomNetGraph *graph = graphs[graphName];
    graph->generateMST(); // TODO: ADD EX EN IN

}

bool ZoomNet::newConnectionBetter(const string& source, const string& destination, int weight, Graph* graph) {
    //graph->setConnection(graph->getNode(source), graph->getNode(destination), weight);
    //int biggestWeight = graph->findBiggestWeight(new Connection{graph->getNode(source), graph->getNode(destination), weight});
    //return biggestWeight > weight;
    return false;
}
