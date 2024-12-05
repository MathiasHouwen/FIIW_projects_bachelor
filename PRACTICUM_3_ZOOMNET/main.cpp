//
// Created by robin on 5/12/2024.
//

#include "src/Graph.h"
#include "src/ZoomNet.h"
#include "src/utils/ZoomNetCLI.h"

int main() {
    ZoomNet zoomNet;
    ZoomNetCLI cli(zoomNet);

    cli.getInput();

//    Graph *graph = new Graph();
//    CityNode *a = new CityNode("a", {});
//    CityNode *b = new CityNode("b", {});
//    CityNode *c = new CityNode("c", {});
//    CityNode *d = new CityNode("d", {});
//    CityNode *e = new CityNode("e", {});
//    CityNode *f = new CityNode("f", {});
//    graph->addNode(a);
//    graph->addNode(b);
//    graph->addNode(c);
//    graph->addNode(d);
//    graph->addNode(e);
//    graph->addNode(f);
//    graph->setConnection(a, b, 11);
//    graph->setConnection(a, c, 10);
//    graph->setConnection(a, e, 13);
//    graph->setConnection(b, d, 9);
//    graph->setConnection(b, f, 21);
//    graph->setConnection(c, f, 8);
//    graph->setConnection(d, e, 12);
//    graph->setConnection(b, e, 7);
//    graph->setConnection(f, d, 18);
//    graph->setConnection(b, c, 15);
//    graph->minimumSpanningTree(a);

}
