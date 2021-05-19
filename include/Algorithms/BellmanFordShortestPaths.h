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
        vertices = graph->GetVertices();
        weighted_edges = graph->GetEdges();
        std::vector<int> tmp;
        for (int & vertex : vertices) {
            dis.insert(std::make_pair(vertex, 0));
            paths.insert(std::make_pair(vertex, tmp));
            vis.insert(std::make_pair(vertex, false));
        }
        dis[source] = 0;
        paths[source].emplace_back(source);

        for (int i = 0; i < vertices.size(); i++) {
            for (int j = 0; j < weighted_edges.size(); j++) {
                int cur_source = weighted_edges[j].GetSource();
                int cur_destination = weighted_edges[j].GetDestination();
                int cur_weight = weighted_edges[j].GetWeight();
                if ((vis[cur_source] && vis[cur_destination]) ||
                    (dis[cur_destination] > dis[cur_source] + cur_weight)) {
                    dis[cur_destination] = dis[cur_source] + cur_weight;
                    paths[cur_destination] = paths[cur_source];
                    paths[cur_destination].emplace_back(cur_destination);
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
    };

    ~BellmanFordShortestPaths() {
        vertices.clear();
        weighted_edges.clear();
        dis.clear();
        vis.clear();
        paths.clear();
    };

    bool HasPathTo(int destination) const {
        if (!this->graph->ContainsVertex(destination)) return false;
        if (dis.at(destination) != std::nullopt)
            return true;
        else
            return false;
    };

    std::optional<typename TGraph::value_type> TryGetDistanceTo(int destination) const {
        if (!this->graph->ContainsVertex(destination)) return std::nullopt;
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
