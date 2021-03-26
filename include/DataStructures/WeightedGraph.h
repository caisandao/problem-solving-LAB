//
// Created by ASUS on 2021/3/13.
//

#ifndef GRAPHLIBRARY_WEIGHTEDGRAPH_H
#define GRAPHLIBRARY_WEIGHTEDGRAPH_H

#include <DataStructures/WeightedEdge.h>
#include <map>
#include <vector>
#include <algorithm>

template <typename T>
class WeightedGraph {
public:
    WeightedGraph() = default;
    virtual ~WeightedGraph() = default;
public:
    bool AddVertex(int vertex) {
        if (ContainsVertex(vertex))
            return false;
        else{
            vertices.push_back(vertex);
            return true;
        }
    };
    bool RemoveVertex(int vertex) {
        bool check = false;
        for (int i = 0 ; i < vertices.size() ; ++i) {
            if (vertices[i] == vertex) {
                vertices.erase(vertices.begin()+i);
                check = true;
                break;
            }
        }
        return check;
    };
    virtual bool AddEdge(int vertex1, int vertex2, T weight) {
        if (ContainsVertex(vertex1) && ContainsVertex(vertex2) && !ContainsEdge(vertex1, vertex2)) {
            edges[vertex1].emplace_back(std::make_pair(vertex2, weight));
            return true;
        }
        else
            return false;
    };
    virtual bool RemoveEdge(int vertex1, int vertex2) {
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
    };
    int CountVertices() const {
        return vertices.size();
    };
    virtual int CountEdges() const {
        int res = 0;
        for (const auto& it : edges) {
            res += it.second.size();
        }
        return res;
    };
    bool ContainsVertex(int vertex) const {
        if (find(vertices.begin(), vertices.end(), vertex) != vertices.end())
            return true;
        else
            return false;
    };
    bool ContainsEdge(int vertex1, int vertex2) const {
        const auto& iter = edges.find(vertex1);
        if (iter != edges.end()) {
            for (const auto& i : iter->second) {
                if (i.first == vertex2) {
                    return true;
                }
            }
        }
        return false;
    };
    T GetWeight(int vertex1, int vertex2) const {
        const auto& iter = edges.find(vertex1);
        if (iter != edges.end()) {
            for (const auto& i : iter->second) {
                if (i.first == vertex2) {
                    return i.second;
                }
            }
        } else {
            return (T)0;
        }
    };
    std::vector<int> GetVertices() const {
        static std::vector<int> temp;
        temp.clear();
        temp  = vertices;
        return temp;
    };
    std::vector<WeightedEdge<T>> GetEdges() const {
        static std::vector<WeightedEdge<T>> temp;
        temp.clear();
        for (const auto& it : edges) {
            for (const auto& i : it.second) {
                WeightedEdge<T> we(it.first, i.first, i.second);
                temp.emplace_back(we);
            }
        }
        return temp;
    };
    std::vector<WeightedEdge<T>> GetIncomingEdges(int vertex) const {
        static std::vector<WeightedEdge<T>> temp;
        temp.clear();
        for (const auto& it : edges) {
            for (const auto i : it.second) {
                if (i.first == vertex) {
                    WeightedEdge<T> we(it.first, i.first, i.second);
                    temp.emplace_back(we);
                }
            }
        }
        return temp;
    };
    std::vector<WeightedEdge<T>> GetOutgoingEdges(int vertex) const {
        static std::vector<WeightedEdge<T>> temp;
        temp.clear();
        for (const auto& it : edges) {
            if (it.first == vertex) {
                for (const auto& i : it.second) {
                    WeightedEdge<T> we(it.first, i.first, i.second);
                    temp.emplace_back(we);
                }
                break;
            }

        }
        return temp;
    };
    virtual int GetDegree(int vertex) const {
        const auto& iter = edges.find(vertex);
        if (iter != edges.end())
            return iter->second.size();
        else
            return 0;
    };
    std::vector<int> GetNeighbors(int vertex) const {
        static std::vector<int> temp;
        temp.clear();
        const auto& iter = edges.find(vertex);
        if (iter != edges.end()) {
            for (const auto& i : iter->second)
                temp.emplace_back(i.first);
        }
        return temp;
    };
public:
    std::map<int, std::vector<std::pair<int, T>>> edges;
    std::vector<int> vertices;
};


#endif //GRAPHLIBRARY_WEIGHTEDGRAPH_H
