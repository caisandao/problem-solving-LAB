//
// Created by ASUS on 2021/5/19.
//

#ifndef GRAPHLIBRARY_BELLMANFORDSHORTESTPATHS_H
#define GRAPHLIBRARY_BELLMANFORDSHORTESTPATHS_H

#include <Algorithms/ShortestPaths.h>
#include <DataStructures/WeightedEdge.h>
#include <unordered_map>

template<typename TGraph>
class BellmanFordShortestPaths : public ShortestPaths<TGraph> {
private:
    bool exist_negative_cyc;
    std::vector<int> vertices;
    std::vector<WeightedEdge<typename TGraph::value_type>> weighted_edges;
    std::unordered_map<int, typename TGraph::value_type> dis;
    std::unordered_map<int, bool> vis;
    std::unordered_map<int, std::vector<int>> paths;
public:
    BellmanFordShortestPaths() = delete;
    BellmanFordShortestPaths(const TGraph *graph, int source) : ShortestPaths<TGraph>(graph, source) {
        if (!graph->ContainsVertex(source)) return;
        vertices = graph->GetVertices();
        weighted_edges = graph->GetEdges();
        std::vector<int> tmp;
        for (int & vertex : vertices) {
            dis.insert(std::make_pair(vertex, typename TGraph::value_type()));
            paths.insert(std::make_pair(vertex, tmp));
            vis.insert(std::make_pair(vertex, false));
        }
        paths[source].emplace_back(source);
        vis[source] = true;

        for (int i = 1; i < vertices.size(); i++) {
            for (int j = 0; j < weighted_edges.size(); j++) {
                int cur_source = weighted_edges[j].GetSource();
                int cur_destination = weighted_edges[j].GetDestination();
                typename TGraph::value_type cur_weight = weighted_edges[j].GetWeight();
                if (!vis[cur_source]) continue;
                if (!vis[cur_destination] ||
                    (dis[cur_destination] > dis[cur_source] + cur_weight)) {
                    dis[cur_destination] = dis[cur_source] + cur_weight;
                    paths[cur_destination] = paths[cur_source];
                    paths[cur_destination].emplace_back(cur_destination);
                    vis[cur_destination] = true;
                }
            }
        }

        exist_negative_cyc = false;
        for (int i = 0; i < weighted_edges.size(); i++) {
            if (dis[weighted_edges[i].GetDestination()] > dis[weighted_edges[i].GetSource()] + weighted_edges[i].GetWeight()) {
                exist_negative_cyc = true;
                break;
            }
        }
        paths[source].emplace_back(source);
    };

    ~BellmanFordShortestPaths() {
        vertices.clear();
        weighted_edges.clear();
        dis.clear();
        vis.clear();
        paths.clear();
    };

    bool HasPathTo(int destination) const {
        //if (exist_negative_cyc) return false;
        if (!this->graph->ContainsVertex(destination)) return false;
        if (this->vis.at(destination))
            return true;
        else
            return false;
    };

    std::optional<typename TGraph::value_type> TryGetDistanceTo(int destination) const {
        //if (exist_negative_cyc) return std::nullopt;
        if (!HasPathTo(destination)) return std::nullopt;
        return dis.at(destination);
    };

    std::optional<std::vector<int>> TryGetShortestPathTo(int destination) const {
        std::vector<int> ret;
        if (!HasPathTo(destination))
            return std::nullopt;
        else {
            ret = paths.at(destination);
            if (ret.empty()) return std::nullopt;
            return ret;
        }
    };
};

#endif //GRAPHLIBRARY_BELLMANFORDSHORTESTPATHS_H
