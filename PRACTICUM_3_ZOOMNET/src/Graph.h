//
// Created by robin on 5/12/2024.
//

#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <unordered_map>
#include <iostream>
#include "Graph.h"
#include <queue>
#include <limits>
#include <iostream>
#include <set>
#include <vector>
#include <unordered_set>

struct Connection;
using namespace std;

struct CityNode{
  std::string city;
  set<Connection*> connections;
};

struct Connection {
  CityNode* start{};
  CityNode* destination{};
  int weight{};
  bool realityCheck{false};

  bool operator<(const Connection& other) const {
    return weight < other.weight;
  }
};

struct ConnectionPointerComparator {
  bool operator()(const Connection* lhs, const Connection* rhs) const {
    return lhs->weight < rhs->weight;
  }
};

class Graph {
public:
  Graph() = default;
  ~Graph() = default;
  void addNode(CityNode* node);
  void removeNode(const CityNode* node);
  CityNode* getNode(const string& city);
  void generateMST(vector<Connection> excludeSet = {}, vector<Connection> includeSet = {});
  std::set<Connection*> getConnections(const string& city);
  void setConnection(CityNode* source, CityNode* destination, int connection);

private:
  unordered_map<string, CityNode*> nodes;
  std::set<Connection*, ConnectionPointerComparator> allConnections;
  bool checkCycle(const CityNode* start, const CityNode* prevNode, unordered_set<string> &visitedNodes);
  static void printroute(const unordered_set<string> &visitedNodes, int distanceTraveled);
};



#endif //GRAPH_H
