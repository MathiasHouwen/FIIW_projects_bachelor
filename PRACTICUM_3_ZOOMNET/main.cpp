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

    cout << "making graph" << endl;
    ZoomNetGraph graph;

    graph.addCity("a");
    graph.addCity("b");
    graph.addCity("c");
    graph.addCity("d");
    graph.addCity("e");
    graph.addCity("f");

    graph.addConnection("a", "b", 11);
    graph.addConnection("a", "c", 10);
    graph.addConnection("a", "e", 13);
    graph.addConnection("b", "c", 15);
    graph.addConnection("b", "d", 9);
    graph.addConnection("b", "e", 7);
    graph.addConnection("b", "f", 21);
    graph.addConnection("c", "f", 8);
    graph.addConnection("d", "e", 12);
    graph.addConnection("f", "d", 18);
    //unordered_set includeSet = {graph.getConnection("b", "f")};
    //unordered_set excludeSet = {graph.getConnection("b", "e")};
    cout << "generating MST" << endl;
    graph.generateMST({}, {});
    cout << graph << endl;
}
