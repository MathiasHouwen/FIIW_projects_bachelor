//
// Created by houwe on 5/12/2024.
//

#include "ZoomNet.h"

void ZoomNet::designMST(string graphName) {
    if (!graphs.contains(graphName)){
//        Graph *graph = new Graph();
//        CityNode *a = new CityNode("a", {});
//        CityNode *b = new CityNode("b", {});
//        CityNode *c = new CityNode("c", {});
//        CityNode *d = new CityNode("d", {});
//        CityNode *e = new CityNode("e", {});
//        CityNode *f = new CityNode("f", {});
//        graph->addCity(a);
//        graph->addCity(b);
//        graph->addCity(c);
//        graph->addCity(d);
//        graph->addCity(e);
//        graph->addCity(f);
//        graph->setConnection(a, b, 11);
//        graph->setConnection(a, c, 10);
//        graph->setConnection(a, e, 13);
//        graph->setConnection(b, d, 9);
//        graph->setConnection(b, f, 21);
//        graph->setConnection(c, f, 8);
//        graph->setConnection(d, e, 12);
//        graph->setConnection(b, e, 7);
//        graph->setConnection(f, d, 18);
//        graph->setConnection(b, c, 15);

       // graphs[graphName] = graph;
    }

    Graph *graph = graphs[graphName];
    graph->generateMST({}, {});

}

void ZoomNet::adaptMST(string graphName) {
    if (!graphs.contains(graphName)){
        designMST(graphName);
    }

    Graph *graph = graphs[graphName];
    graph->generateMST(); // TODO: ADD EX EN IN

}

bool ZoomNet::newConnectionBetter(const string& source, const string& destination, int weight, Graph* graph) {
    //graph->setConnection(graph->getNode(source), graph->getNode(destination), weight);
    //int biggestWeight = graph->findBiggestWeight(new Connection{graph->getNode(source), graph->getNode(destination), weight});
    //return biggestWeight > weight;
}
