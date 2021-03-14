//
// Created by ASUS on 2021/3/13.
//

#include <DataStructures/WeightedGraph.h>
#include <algorithm>

WeightedGraph::WeightedGraph() = default;

WeightedGraph::~WeightedGraph() {
    edges.clear();
    vertices.clear();
};

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
    for (int i = 0 ; i < vertices.size() ; ++i) {
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
        edges[vertex1] = std::vector<std::pair<int, int>>();
        edges[vertex1].emplace_back(std::make_pair(vertex2, weight));
        return true;
    }
    else
        return false;
}

bool WeightedGraph::RemoveEdge(int vertex1, int vertex2) {
    /*
    if (!ContainsVertex(vertex1) || !ContainsVertex(vertex2) || !ContainsEdge(vertex1, vertex2))
        return false;
    else{
        for (int i = 0 ; i < edges[vertex1].size() ; ++i) {
            if (edges[vertex1][i].first == vertex2) {
                edges[vertex1].erase(edges[vertex1].begin()+i);
                return true;
            }
        }
    }
     */

    const auto& it = edges.find(vertex1);
    bool check = false;
    if (it != edges.end()) {
        for (int i = 0 ; i < edges[vertex1].size() ; ++i) {
            if (edges[vertex1][i].first == vertex2) {
                edges[vertex1].erase(edges[vertex1].begin()+i);
                check = true;
                break;
            }
        }
    }
    return check;
    /*
    bool check = false;
    for (int i = 0 ; i < edges[vertex1].size() ; ++i) {
        if (edges[vertex1][i].first == vertex2) {
            edges[vertex1].erase(edges[vertex1].begin()+i);
            check = true;
            break;
        }
    }
    return check;
    */
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
    //std::vector<int>::iterator iter;
    if (find(vertices.begin(), vertices.end(), vertex) != vertices.end())
        return true;
    else
        return false;
    /*
    bool check = false;
    for (int v : vertices) {
        if (v == vertex) {
            return true;
        }
    }
    return check;
     */
}

bool WeightedGraph::ContainsEdge(int vertex1, int vertex2) const {
    const auto& iter = edges.find(vertex1);
    if (iter != edges.end()) {
        for (const auto& i : iter->second) {
            if (i.first == vertex2) {
                return true;
            }
        }
    }
    return false;
    /*
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
     */
}

int WeightedGraph::GetWeight(int vertex1, int vertex2) const {
    const auto& iter = edges.find(vertex1);
    if (iter != edges.end()) {
        for (const auto& i : iter->second) {
            if (i.first == vertex2) {
                return i.second;
            }
        }
    } else {
        return 0;
    }

    /*
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
     */
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
    const auto& iter = edges.find(vertex);
    if (iter != edges.end())
        return iter->second.size();
    else
        return 0;
    /*
    for (const auto& it : edges) {
        if (it.first == vertex) {
            return it.second.size();
        }
    }
     */
}

std::vector<int> WeightedGraph::GetNeighbors(int vertex) const {
    static std::vector<int> temp;
    temp.clear();
    const auto& iter = edges.find(vertex);
    if (iter != edges.end()) {
        for (const auto& i : iter->second)
            temp.emplace_back(i.first);
    }
    return temp;
    /*
    for (const auto& it : edges) {
        if (it.first == vertex) {
            for (const auto& i : it.second)
                temp.emplace_back(i.first);
        }
    }
    return temp;
     */
}