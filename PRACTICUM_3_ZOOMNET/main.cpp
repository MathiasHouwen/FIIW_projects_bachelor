//
// Created by robin on 5/12/2024.
//

#include "src/Graph.h"
#include "src/ZoomNet.h"
#include "src/utils/ZoomNetCLI.h"

int main() {
//    ZoomNet zoomNet;
//    ZoomNetCLI cli(zoomNet);
//
//    cli.getInput();

    auto *graph = new Graph();
    auto *a = new CityNode("a", {});
    auto *b = new CityNode("b", {});
    auto *c = new CityNode("c", {});
    auto *d = new CityNode("d", {});
    auto *e = new CityNode("e", {});
    auto *f = new CityNode("f", {});
    graph->addCity(a);
    graph->addCity(b);
    graph->addCity(c);
    graph->addCity(d);
    graph->addCity(e);
    graph->addCity(f);
    graph->setConnection(a, b, 11);
    graph->setConnection(a, c, 10);
    graph->setConnection(a, e, 13);
    graph->setConnection(b, d, 9);
    graph->setConnection(b, f, 21);
    graph->setConnection(c, f, 8);
    graph->setConnection(d, e, 12);
    graph->setConnection(b, e, 7);
    graph->setConnection(f, d, 18);
    graph->setConnection(b, c, 15);
    unordered_set includeSet = {graph->getConnection(b, f)};
    unordered_set excludeSet = {graph->getConnection(b, e)};
    graph->generateMST(excludeSet, includeSet);

}
