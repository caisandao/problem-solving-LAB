//
// Created by ASUS on 2021/3/13.
//


/*
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
 */

#include <DataStructures/WeightedGraph.h>

WeightedGraph::WeightedGraph() {}

WeightedGraph::~WeightedGraph() {}

bool WeightedGraph::AddVertex(int vertex) {
    if (ContainsVertex(vertex))
        return false;
    else{
        vertices.push_back(vertex);
        return true;
    }
}

bool WeightedGraph::RemoveVertex(int vertex) {
    bool check = false;
    for (int i = 0 ; i < vertices.size(); ++i) {
        if (vertices[i] == vertex) {
            vertices.erase(vertices.begin()+i);
            check = true;
            break;
        }
    }
    return check;
}

bool WeightedGraph::AddEdge(int vertex1, int vertex2, int weight) {
    if (ContainsVertex(vertex1) && ContainsVertex(vertex2) && !ContainsEdge(vertex1, vertex2)) {
        edges[vertex1].emplace_back(std::make_pair(vertex2, weight));
        return true;
    }
    else
        return false;
}

bool WeightedGraph::RemoveEdge(int vertex1, int vertex2) {
    bool check = false;
    for (int i = 0 ; i < edges[vertex1].size() ; ++i) {
        if (edges[vertex1][i].first == vertex2) {
            edges[vertex1].erase(edges[vertex1].begin()+i);
            check = true;
            break;
        }
    }
    return check;
}

int WeightedGraph::CountVertices() const {
    return vertices.size();
}

int WeightedGraph::CountEdges() const {
    int res = 0;
    for (const auto& it : edges) {
        res += it.second.size();
    }
    return res;
}

bool WeightedGraph::ContainsVertex(int vertex) const {
    bool check = false;
    for (int vertice : vertices) {
        if (vertice == vertex) {
            return true;
        }
    }
    return check;
}

bool WeightedGraph::ContainsEdge(int vertex1, int vertex2) const {
    bool check = false;
    for (const auto& it : edges) {
        if (it.first == vertex1) {
            for (const auto& i : it.second) {
                if (i.first == vertex2){
                    return true;
                }
            }
        }
    }
    return check;
}

int WeightedGraph::GetWeight(int vertex1, int vertex2) const {
    int res = 0; // 若没有这条边则为未定义行为，此处返回0
    for (const auto& it : edges) {
        if (it.first == vertex1) {
            for (const auto& i : it.second) {
                if (i.first == vertex2)
                    return i.second;
            }
        }
    }
    return res;
}

std::vector<int> WeightedGraph::GetVertices() const {
    static std::vector<int> temp;
    temp.clear();
    temp  = vertices;
    return temp;
}

std::vector<WeightedEdge> WeightedGraph::GetEdges() const {
    static std::vector<WeightedEdge> temp;
    temp.clear();
    for (const auto& it : edges) {
        for (const auto& i : it.second) {
            WeightedEdge we(it.first, i.first, i.second);
            temp.emplace_back(we);
        }
    }
    return temp;
}

std::vector<WeightedEdge> WeightedGraph::GetIncomingEdges(int vertex) const {
    static std::vector<WeightedEdge> temp;
    temp.clear();
    for (const auto& it : edges) {
        for (const auto i : it.second) {
            if (i.first == vertex) {
                WeightedEdge we(it.first, i.first, i.second);
                temp.emplace_back(we);
            }
        }
    }
    return temp;
}

std::vector<WeightedEdge> WeightedGraph::GetOutgoingEdges(int vertex) const {
    static std::vector<WeightedEdge> temp;
    temp.clear();
    for (const auto& it : edges) {
        if (it.first == vertex) {
            for (const auto& i : it.second) {
                WeightedEdge we(it.first, i.first, i.second);
                temp.emplace_back(we);
            }
        }
        break;
    }
    return temp;
}

int WeightedGraph::GetDegree(int vertex) const {
    for (const auto& it : edges) {
        if (it.first == vertex) {
            return it.second.size();
        }
    }
}

std::vector<int> WeightedGraph::GetNeighbors(int vertex) const {
    static std::vector<int> temp;
    temp.clear();
    for (const auto& it : edges) {
        if (it.first == vertex) {
            for (const auto& i : it.second)
                temp.emplace_back(i.first);
        }
    }
    return temp;
}