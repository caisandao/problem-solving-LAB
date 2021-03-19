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
    if (vertex1 == vertex2)
        return WeightedGraph::AddEdge(vertex1, vertex2, weight);
    else {
        bool check1 = false, check2 = false;
        check1 = WeightedGraph::AddEdge(vertex1, vertex2, weight);
        check2 = WeightedGraph::AddEdge(vertex2, vertex1, weight);
        return check1 && check2;
    }
}

bool UndirectedWeightedGraph::RemoveEdge(int vertex1, int vertex2) {
    if (vertex1 == vertex2)
        return WeightedGraph::RemoveEdge(vertex1, vertex2);
    else {
        bool check1 = false, check2 = false;
        check1 = WeightedGraph::RemoveEdge(vertex1, vertex2);
        check2 = WeightedGraph::RemoveEdge(vertex2, vertex1);
        return check1 && check2;
    }
}

int UndirectedWeightedGraph::CountEdges() const {
    int res = 0;
    for (const auto& it : edges) {
        for (const auto& i: it.second) {
            if (i.first == it.first)
                res += 2;
            else
                res++;
        }
    }
    return res / 2;
}

std::vector<WeightedEdge> UndirectedWeightedGraph::GetEdges() const {

    static std::vector<WeightedEdge> temp;
    temp.clear();
    int check = 0;
    for (const auto& it : edges) {
        for (const auto& i : it.second) {
            WeightedEdge we(it.first, i.first, i.second);
            for (auto & j : temp) {
                if (j.GetSource() == we.GetDestination() && j.GetDestination() == we.GetSource()) {
                    check = 1;
                    break;
                }
            }
            if (!check)
                temp.emplace_back(we);
            check = 0;
        }
    }
    return temp;

}
