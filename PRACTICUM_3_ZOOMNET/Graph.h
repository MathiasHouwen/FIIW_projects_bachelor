//
// Created by robin on 5/12/2024.
//

#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <unordered_map>
#include <iostream>
#include <unordered_set>

using namespace std;

struct CityNode{
  std::string city;
  std::unordered_map<CityNode*, int> connections;
};

class Graph {
public:
  Graph() = default;
  ~Graph() = default;
  void addNode(CityNode* node);
  void removeNode(CityNode* node);
  std::unordered_map<CityNode*, int> getConnections(string city);
  void getShortestPath(CityNode* source, CityNode* destination);
  static void setConnection(CityNode* source, CityNode* destination, int connection);

private:
  unordered_map<string, CityNode*> nodes;
  void visitCity(CityNode* node, int distanceTraveled, CityNode* destination, unordered_set<string>& visitedNodes);
  void printroute(unordered_set<string>& visitedNodes, int distanceTraveled);
};



#endif //GRAPH_H
