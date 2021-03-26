//
// Created by ASUS on 2021/3/19.
//

#ifndef GRAPHLIBRARY_UNDIRECTEDWEIGHTEDGRAPH_H
#define GRAPHLIBRARY_UNDIRECTEDWEIGHTEDGRAPH_H

#include <DataStructures/WeightedGraph.h>

template <typename T>
class UndirectedWeightedGraph : public WeightedGraph<T> {
public:
    bool AddEdge(int vertex1, int vertex2, int weight) {
        if (vertex1 == vertex2)
            return WeightedGraph<T>::AddEdge(vertex1, vertex2, weight);
        else {
            bool check1 = false, check2 = false;
            check1 = WeightedGraph<T>::AddEdge(vertex1, vertex2, weight);
            check2 = WeightedGraph<T>::AddEdge(vertex2, vertex1, weight);
            return check1 && check2;
        }
    };
    bool RemoveEdge(int vertex1, int vertex2) {
        if (vertex1 == vertex2)
            return WeightedGraph<T>::RemoveEdge(vertex1, vertex2);
        else {
            bool check1 = false, check2 = false;
            check1 = WeightedGraph<T>::RemoveEdge(vertex1, vertex2);
            check2 = WeightedGraph<T>::RemoveEdge(vertex2, vertex1);
            return check1 && check2;
        }
    };
    int CountEdges() const {
        int res = 0;
        for (const auto& it : WeightedGraph<T>::edges) {
            for (const auto& i: it.second) {
                if (i.first == it.first)
                    res += 2;
                else
                    res++;
            }
        }
        return res / 2;
    };
    std::vector<WeightedEdge<T>> GetEdges() const {
        static std::vector<WeightedEdge<int>> temp;
        temp.clear();
        int check = 0;
        for (const auto& it : WeightedGraph<T>::edges) {
            for (const auto& i : it.second) {
                WeightedEdge<int> we(it.first, i.first, i.second);
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
    };
    int GetDegree(int vertex) const {
        const auto& iter = WeightedGraph<T>::edges.find(vertex);
        int res = 0;
        if (iter != WeightedGraph<T>::edges.end()) {
            for (const auto& i : iter->second) {
                if (i.first == iter->first)
                    res += 2;
                else
                    res++;
            }
            return res;
        }
        else
            return 0;
    };
};


#endif //GRAPHLIBRARY_UNDIRECTEDWEIGHTEDGRAPH_H
