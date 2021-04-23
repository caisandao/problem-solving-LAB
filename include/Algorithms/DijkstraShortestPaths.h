//
// Created by ASUS on 2021/4/22.
//

#ifndef GRAPHLIBRARY_DIJKSTRASHORTESTPATHS_H
#define GRAPHLIBRARY_DIJKSTRASHORTESTPATHS_H

#include <Algorithms/ShortestPaths.h>
#include <unordered_map>
#include <vector>
#include <queue>


template <template<typename> class TGraph, typename TValue>
class DijkstraShortestPaths : public ShortestPaths<TGraph, TValue> {
private:
    std::unordered_map<int, bool> vis;
    std::unordered_map<int, std::optional<TValue>> dis;
    std::vector<int> vertices;
    std::unordered_map<int, std::vector<int>> paths;
public:
    DijkstraShortestPaths() = delete;
    DijkstraShortestPaths(const TGraph<TValue> *graph, int source) : ShortestPaths<TGraph, TValue>(graph, source) {
        if (!graph->ContainsVertex(source)) return;
        vertices = graph->GetVertices();
        for (int & vertex : vertices) {
            vis.insert(std::make_pair(vertex, false));
            dis.insert(std::make_pair(vertex, std::nullopt));
            //paths[vertex].emplace_back(source);
            //paths[vertex].emplace_back(vertex);
        }
        std::priority_queue<std::pair<std::optional<TValue>, int>, std::vector<std::pair<std::optional<TValue>, int>>, std::greater<std::pair<std::optional<TValue>, int>>> pq;
        dis[source] = TValue();
        pq.emplace(TValue(), source);
        paths[source].emplace_back(source);
        while (!pq.empty()) {
            const auto  state = pq.top();
            pq.pop();
            const std::optional<TValue> cur_dis = state.first;
            const int cur_idx = state.second;
            if (vis[cur_idx]) continue;
            vis[cur_idx] = true;
            for (const auto& edge : graph->edges[cur_idx]) {
                const std::optional<TValue> new_dis = cur_dis + edge.second;
                const int new_idx = edge.first;
                if (dis[new_idx] == std::nullopt || new_dis < dis[new_idx])  {
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
        if (dis[destination] != std::nullopt)
            return true;
        else
            return false;
    };
    std::optional<TValue> TryGetDistanceTo(int destination) const {
        return dis[destination];
    };
    std::optional<std::vector<int>> TryGetShortestPathTo(int destination) const {
        if (!HasPathTo(destination))
            return std::nullopt;
        else
            return this->paths[destination];
    };
};

#endif //GRAPHLIBRARY_DIJKSTRASHORTESTPATHS_H
