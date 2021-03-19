//
// Created by ASUS on 2021/3/19.
//

#include <DataStructures/UndirectedGraph.h>
#include <algorithm>

bool UndirectedGraph::AddEdge(int vertex1, int vertex2) {
    if (vertex1 == vertex2)
        return Graph::AddEdge(vertex1, vertex2);
    else {
        bool check1 = false, check2 = false;
        check1 = Graph::AddEdge(vertex1, vertex2);
        check2 = Graph::AddEdge(vertex2, vertex1);
        return check1 && check2;
    }
}

bool UndirectedGraph::RemoveEdge(int vertex1, int vertex2) {
    if (vertex1 == vertex2)
        return Graph::RemoveEdge(vertex1, vertex2);
    else {
        bool check1 = false, check2 = false;
        check1 = Graph::RemoveEdge(vertex1, vertex2);
        check2 = Graph::RemoveEdge(vertex2, vertex1);
        return check1 && check2;
    }
}

int UndirectedGraph::CountEdges() const {
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

std::vector<Edge> UndirectedGraph::GetEdges() const {
    static std::vector<Edge> temp;
    temp.clear();
    int check = 0;
    for (const auto& it : edges) {
        for (const auto& i : it.second) {
            Edge e(it.first, i.first);
            for (auto & j : temp) {
                if (j.GetSource() == e.GetDestination() && j.GetDestination() == e.GetSource()) {
                    check = 1;
                    break;
                }
            }
            if (!check)
                temp.emplace_back(e);
            check = 0;
        }
    }
    return temp;
}