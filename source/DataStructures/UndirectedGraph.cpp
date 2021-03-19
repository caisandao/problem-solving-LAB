//
// Created by ASUS on 2021/3/19.
//

#include <DataStructures/UndirectedGraph.h>
#include <algorithm>

bool UndirectedGraph::AddEdge(int vertex1, int vertex2, int weight) {
    Graph::AddEdge(vertex1, vertex2);
    Graph::AddEdge(vertex2, vertex1);
}

bool UndirectedGraph::RemoveEdge(int vertex1, int vertex2) {
    Graph::RemoveEdge(vertex1, vertex2);
    Graph::RemoveEdge(vertex2, vertex1);
}

int UndirectedGraph::CountEdges() const {
    return Graph::CountEdges() / 2;
}

std::vector<Edge> UndirectedGraph::GetEdges() const {
    static std::vector<Edge> temp;
    temp.clear();
    int check = 0;
    for (const auto& it : edges) {
        for (const auto& i : it.second) {
            Edge e(it.first, i.first);
            Edge inverse_e(i.first, it.first);
            for (auto & j : temp) {
                if (j.GetSource() == inverse_e.GetSource() && j.GetDestination() == inverse_e.GetDestination()) {
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