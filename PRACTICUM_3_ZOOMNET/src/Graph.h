//
// Created by robin on 5/12/2024.
//

#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <unordered_map>
#include <iostream>
#include <unordered_set>
#include "Graph.h"
#include <queue>
#include <limits>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <vector>

using namespace std;

struct CityNode{
  std::string city;
  std::unordered_map<CityNode*, int> connections;
};

struct Edge {
  CityNode* source;
  CityNode* destination;
  int weight;

  // Custom comparator for priority queue (min-heap)
  bool operator>(const Edge& other) const {
    return weight > other.weight;
  }
};

class Graph {
public:
  Graph() = default;
  ~Graph() = default;
  void addNode(CityNode* node);
  void removeNode(CityNode* node);
  CityNode* getNode(const string& city);

  std::unordered_map<CityNode*, int> getConnections(string city);

  static void minimumSpanningTree(CityNode *start);

  static void setConnection(CityNode* source, CityNode* destination, int connection);

private:
  unordered_map<string, CityNode*> nodes;
};



#endif //GRAPH_H
