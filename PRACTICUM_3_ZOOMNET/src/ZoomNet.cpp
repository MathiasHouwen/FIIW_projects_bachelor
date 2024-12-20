// taakverdeling en uitleg: zie h-file


#include "ZoomNet.h"
using namespace std;

void ZoomNet::designMST() {
    ZoomNetGraph graph{};

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

    graph.clearConnections();
    graph.generateMST({}, {});
    cout << graph << endl;
}

void ZoomNet::adaptMST() {

    ZoomNetGraph graph{};

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

    graph.clearConnections();

    unordered_set includeSet = {graph.getConnection("b", "f")};
    unordered_set excludeSet = {graph.getConnection("b", "e")};

    graph.generateMST(includeSet, excludeSet);
    cout << graph << endl;
}

bool ZoomNet::newConnectionBetter(const std::string& city1, const std::string& city2, int w) {
    ZoomNetGraph graph{};

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

    graph.clearConnections();
    graph.generateMST();

    // bool better = graph.isNewConnectionBetter("C", "D", 5);
    bool better = graph.isNewConnectionBetter(city1, city2, w);
    cout << (better ? "yes, better" : "no, not better") << endl;
    return better;
}

void ZoomNet::generateChannels() {

    ZoomNetGraph graph{};

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

    graph.clearConnections();
    graph.generateMST({}, {});
    graph.generateRealChannels();
    cout << graph << endl;

}

void ZoomNet::colourGraph() {

    ZoomNetGraph graph{};

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

    graph.clearConnections();
    graph.generateMST({}, {});
    graph.generateALlPossibleChannels();
    cout << graph << endl;

}

//ZoomNet::ZoomNet() {
//    graph.addCity("a");
//    graph.addCity("b");
//    graph.addCity("c");
//    graph.addCity("d");
//    graph.addCity("e");
//    graph.addCity("f");
//
//    graph.addConnection("a", "b", 11);
//    graph.addConnection("a", "c", 10);
//    graph.addConnection("a", "e", 13);
//    graph.addConnection("b", "c", 15);
//    graph.addConnection("b", "d", 9);
//    graph.addConnection("b", "e", 7);
//    graph.addConnection("b", "f", 21);
//    graph.addConnection("c", "f", 8);
//    graph.addConnection("d", "e", 12);
//    graph.addConnection("f", "d", 18);
//}