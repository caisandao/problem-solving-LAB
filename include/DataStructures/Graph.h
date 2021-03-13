#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <DataStructures/Edge.h>
#include <DataStructures/WeightedGraph.h>

/*
class Graph {
 public:
  Graph();
  ~Graph();
 public:
  bool AddVertex(int vertex);
  bool RemoveVertex(int vertex);
  bool AddEdge(int vertex1, int vertex2);
  bool RemoveEdge(int vertex1, int vertex2);
 public:
  int CountVertices() const;
  int CountEdges() const;
  bool ContainsVertex(int vertex) const;
  bool ContainsEdge(int vertex1, int vertex2) const;
  std::vector<int> GetVertices() const;
  std::vector<Edge> GetEdges() const;
  std::vector<Edge> GetIncomingEdges(int vertex) const;
  std::vector<Edge> GetOutgoingEdges(int vertex) const;
  int GetDegree(int vertex) const;
  std::vector<int> GetNeighbors(int vertex) const;
 private:
  std::vector<Edge> edges;
  std::vector<int> vertices;
};
*/

class Graph : public WeightedGraph {
public:
    bool AddEdge(int vertex1, int vertex2);
    std::vector<Edge> GetEdges() const;
    std::vector<Edge> GetIncomingEdges(int vertex) const;
    std::vector<Edge> GetOutgoingEdges(int vertex) const;
private:
    std::map<int, std::vector<std::pair<int, int>>> edges;
    std::vector<int> vertices;
};

// 函数的值只应该出现在.cpp文件内，不要再在.h文件内再声明

#endif
