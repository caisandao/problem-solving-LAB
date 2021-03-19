//
// Created by ASUS on 2021/3/19.
//

#include <DataStructures/UndirectedWeightedGraph.h>
#include <algorithm>
/*
bool AddEdge(int vertex1, int vertex2, int weight);
bool RemoveEdge(int vertex1, int vertex2);
virtual int CountEdges() const;
virtual std::vector<WeightedEdge> GetEdges() const;
 */

bool UndirectedWeightedGraph::AddEdge(int vertex1, int vertex2, int weight) {
    WeightedGraph::AddEdge(vertex1, vertex2, weight);
    WeightedGraph::AddEdge(vertex2, vertex1, weight);
}

bool UndirectedWeightedGraph::RemoveEdge(int vertex1, int vertex2) {
    WeightedGraph::RemoveEdge(vertex1, vertex2);
    WeightedGraph::RemoveEdge(vertex2, vertex1);
}

int UndirectedWeightedGraph::CountEdges() const {
    return WeightedGraph::CountEdges() / 2;
}

std::vector<WeightedEdge> UndirectedWeightedGraph::GetEdges() const {

    static std::vector<WeightedEdge> temp;
    temp.clear();
    for (const auto& it : edges) {
        for (const auto& i : it.second) {
            const WeightedEdge we(it.first, i.first, i.second);
            const WeightedEdge inverse_we(i.first, it.first, i.second);
            if (find(temp.begin(), temp.end(), inverse_we) == temp.end())
                temp.emplace_back(we);
        }
    }
    return temp;

}
