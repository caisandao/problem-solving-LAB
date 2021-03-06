//
// Created by ASUS on 2021/4/22.
//

#ifndef GRAPHLIBRARY_DIJKSTRASHORTESTPATHS_H
#define GRAPHLIBRARY_DIJKSTRASHORTESTPATHS_H

#include <Algorithms/ShortestPaths.h>
#include <unordered_map>
#include <vector>
#include <queue>


//template <template<typename> class TGraph, typename TValue>
template<typename TGraph>
class DijkstraShortestPaths : public ShortestPaths<TGraph> {
private:
    std::unordered_map<int, bool> vis;
    std::unordered_map<int, std::optional<typename TGraph::value_type>> dis;
    std::vector<int> vertices;
    std::unordered_map<int, std::vector<int>> paths;
public:
    DijkstraShortestPaths() = delete;
    DijkstraShortestPaths(const TGraph *graph, int source) : ShortestPaths<TGraph>(graph, source) {
        vis.clear();
        dis.clear();
        vertices.clear();
        paths.clear();
        vertices = graph->GetVertices();
        std::vector<int> tmp;
        for (int & vertex : vertices) {
            vis.insert(std::make_pair(vertex, false));
            dis.insert(std::make_pair(vertex, std::nullopt));
            paths.insert(std::make_pair(vertex, tmp));
        }

        if (!graph->ContainsVertex(source)) return;
        std::priority_queue<std::pair<typename TGraph::value_type, int>, std::vector<std::pair<typename TGraph::value_type, int>>, std::greater<std::pair<typename TGraph::value_type, int>>> pq;
        dis[source] = typename TGraph::value_type();
        pq.emplace(typename TGraph::value_type(), source);
        paths[source].emplace_back(source);
        while (!pq.empty()) {
            const auto state = pq.top();
            pq.pop();
            const typename TGraph::value_type cur_dis = state.first;
            const int cur_idx = state.second;
            if (vis[cur_idx]) continue;
            vis[cur_idx] = true;
            for (const auto& edge : graph->GetOutgoingEdges(cur_idx)) {
                const typename TGraph::value_type new_dis = cur_dis + edge.GetWeight();
                const int new_idx = edge.GetDestination();
                if (dis[new_idx] == std::nullopt || new_dis < dis[new_idx]) {
                    pq.push({new_dis, new_idx});
                    dis[new_idx] = new_dis;
                    paths[new_idx] = paths[cur_idx];
                    paths[new_idx].emplace_back(new_idx);
                }
            }
        }

    };
    ~DijkstraShortestPaths() {
        vis.clear();
        dis.clear();
        vertices.clear();
        paths.clear();
    };
    bool HasPathTo(int destination) const {
        //return false;
        if (!this->graph->ContainsVertex(destination)) return false;
        if (dis.at(destination) != std::nullopt)
            return true;
        else
            return false;
    };
    std::optional<typename TGraph::value_type> TryGetDistanceTo(int destination) const {
        //return std::nullopt;
        if (!this->graph->ContainsVertex(destination)) return std::nullopt;
        return dis.at(destination);
    };
    std::optional<std::vector<int>> TryGetShortestPathTo(int destination) const {
        //return std::nullopt;
        //if (!this->graph->ContainsVertex(destination)) return std::nullopt;
        std::vector<int> ret;
        if (!HasPathTo(destination))
            //return ret;
            return std::nullopt;
        else {
            ret = paths.at(destination);
            if (ret.empty()) return std::nullopt;
            return ret;
        }
    };
};

#endif //GRAPHLIBRARY_DIJKSTRASHORTESTPATHS_H

/*
            for (auto iter = graph->edges.at(cur_idx).begin(); iter != graph->edges.at(cur_idx).end(); iter++) {

                const TValue new_dis = cur_dis + (*iter).second;
                const int new_idx = (*iter).first;
                if (dis[new_idx] == std::nullopt || new_dis < dis[new_idx]) {
                    pq.push({new_dis, new_idx});
                    dis[new_idx] = new_dis;
                    paths[new_idx] = paths[cur_idx];
                    paths[new_idx].emplace_back(new_idx);
                }

            }
             */