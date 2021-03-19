//
// Created by ASUS on 2021/3/19.
//

#ifndef GRAPHLIBRARY_UNDIRECTEDWEIGHTEDGRAPH_H
#define GRAPHLIBRARY_UNDIRECTEDWEIGHTEDGRAPH_H

#include <DataStructures/WeightedGraph.h>

class UndirectedWeightedGraph : public WeightedGraph {
public:
    bool AddEdge(int vertex1, int vertex2, int weight);
    bool RemoveEdge(int vertex1, int vertex2);
    int CountEdges() const;
    std::vector<WeightedEdge> GetEdges() const;
};

#endif //GRAPHLIBRARY_UNDIRECTEDWEIGHTEDGRAPH_H
