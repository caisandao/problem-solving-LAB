//
// Created by ASUS on 2021/3/19.
//

#ifndef GRAPHLIBRARY_UNDIRECTEDGRAPH_H
#define GRAPHLIBRARY_UNDIRECTEDGRAPH_H

#include <DataStructures/Graph.h>

class UndirectedGraph : public Graph {
public:
    bool AddEdge(int vertex1, int vertex2);
    bool RemoveEdge(int vertex1, int vertex2);
    int CountEdges() const;
    std::vector<Edge> GetEdges() const;
};

#endif //GRAPHLIBRARY_UNDIRECTEDGRAPH_H
