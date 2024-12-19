//
// Created by robin on 5/12/2024.
//

#include "src/graph/Graph.h"
#include "src/ZoomNet.h"
#include "src/utils/ZoomNetCLI.h"

int main() {
//    ZoomNet zoomNet;
//    ZoomNetCLI cli(zoomNet);
//
//    cli.getInput();

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

    cout << "=== Initiele MST: =========================================" << endl;
    graph.generateMST({}, {});
    cout << graph << endl;

    cout << "=== MST Met include exclude: ==============================" << endl;
    graph.clearConnections();
    graph.generateMST(excludeSet, includeSet);
    cout << graph << endl;

    cout << "=== New connection better: ================================" << endl;
    graph.clearConnections();
    graph.generateMST();
    bool better = graph.isNewConnectionBetter("C", "D", 5);
    cout << (better ? "yes, better" : "no, not better") << endl;

    cout << "=== Channels echte net: ================================" << endl;
    graph.generateRealChannels();
    cout << graph << endl;
    cout << "=== Channels alle possible connecties: ================================" << endl;
    graph.clearConnections();
    graph.generateMST();
    graph.generateALlPossibleChannels();
    cout << graph << endl;
}
