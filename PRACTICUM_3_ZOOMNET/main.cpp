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

    graph.addCity("A");
    graph.addCity("B");
    graph.addCity("C");
    graph.addCity("D");
    graph.addCity("E");
    graph.addCity("F");

    graph.addConnection("A", "B", 11);
    graph.addConnection("A", "C", 10);
    graph.addConnection("A", "E", 13);
    graph.addConnection("B", "C", 15);
    graph.addConnection("B", "D", 9);
    graph.addConnection("B", "E", 7);
    graph.addConnection("B", "F", 21);
    graph.addConnection("C", "F", 8);
    graph.addConnection("D", "E", 12);
    graph.addConnection("F", "D", 18);
    unordered_set includeSet = {graph.getConnection("B", "F")};
    unordered_set excludeSet = {graph.getConnection("B", "E")};
    //includeSet = {};
    //excludeSet = {};
    cout << "generating MST" << endl;
    graph.generateMST(excludeSet, includeSet);
    cout << graph << endl;
}
