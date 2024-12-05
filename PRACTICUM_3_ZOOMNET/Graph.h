//
// Created by robin on 5/12/2024.
//

#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <unordered_map>

struct CityNode{
  std::string city;
  std::unordered_map<CityNode*, int> connections;
};

class Graph {
public:
  Graph();
  ~Graph();
  void addNode(CityNode* node);
  void removeNode(CityNode* node);
  std::unordered_map<CityNode*, int> getConnections();
  void getShortestPath(CityNode* source, CityNode* destination);

private:
  std::unordered_map<CityNode*, CityNode*> nodes;
};



#endif //GRAPH_H
