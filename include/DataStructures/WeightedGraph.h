//
// Created by ASUS on 2021/3/13.
//

#ifndef GRAPHLIBRARY_WEIGHTEDGRAPH_H
#define GRAPHLIBRARY_WEIGHTEDGRAPH_H

#include <DataStructures/WeightedEdge.h>
#include <map>
#include <vector>

class WeightedGraph {
public:
    WeightedGraph();
    ~WeightedGraph();
public:
    bool AddVertex(int vertex);
    bool RemoveVertex(int vertex);
    bool AddEdge(int vertex1, int vertex2, int weight);
    bool RemoveEdge(int vertex1, int vertex2);
    int CountVertices() const;
    int CountEdges() const;
    bool ContainsVertex(int vertex) const;
    bool ContainsEdge(int vertex1, int vertex2) const;
    int GetWeight(int vertex1, int vertex2) const;
    std::vector<int> GetVertices() const;
    std::vector<WeightedEdge> GetEdges() const;
    std::vector<WeightedEdge> GetIncomingEdges(int vertex) const;
    std::vector<WeightedEdge> GetOutgoingEdges(int vertex) const;
    int GetDegree(int vertex) const;
    std::vector<int> GetNeighbors(int vertex) const;
private:
    std::map<int, std::vector<std::pair<int, int>>> edges;
    std::vector<int> vertices;
};


#endif //GRAPHLIBRARY_WEIGHTEDGRAPH_H
