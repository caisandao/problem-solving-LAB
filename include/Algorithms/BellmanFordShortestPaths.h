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
        //weighted_edges = graph->GetEdges();
        std::vector<WeightedEdge<typename TGraph::value_type>> tmp_w;
        for (auto & vertex : vertices) {
            tmp_w = graph->GetOutgoingEdges(vertex);
            for (int i = 0; i < tmp_w.size(); i++) {
                weighted_edges.emplace_back(tmp_w[i]);
            }
        }
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


//
// Created by mojito on 2021/4/28.
//

/*
#ifndef GRAPHLIBRARY_BELLMANFORDSHORTESTPATHS_H
#define GRAPHLIBRARY_BELLMANFORDSHORTESTPATHS_H

#include "Algorithms/ShortestPaths.h"
//#include "Exceptions/NegativeCycleException.h"
#include <queue>
#include <set>

#define SPDistance ShortestPaths<TGraph>::Distance
#define SPPath ShortestPaths<TGraph>::Path

template<typename TGraph>
class BellmanFordShortestPaths : public ShortestPaths<TGraph> {
public:
    typedef typename TGraph::value_type TValue;

public:
    BellmanFordShortestPaths() = delete;

    ~BellmanFordShortestPaths() = default;

    BellmanFordShortestPaths(const TGraph *graph, int source) : ShortestPaths<TGraph>(graph, source){
        std::unordered_map<int, int> in_queue_times;
        std::vector<int> vertex = graph->GetVertices();
        int max_times = vertex.size();
        for(int vtx : vertex)
            in_queue_times.emplace(vtx, 0);

        if (!graph->ContainsVertex(source))  return;
        std::queue<int> q;
        std::set<int> in_queue;
        q.push(source);
        in_queue_times[source]++;

        in_queue.emplace(source);
        while (!q.empty()){
            int cur_idx = q.front();    q.pop();

            //if (in_queue_times[cur_idx] > max_times)//负环
            //    throw NegativeCycleException("Bellman-Ford");

            TValue cur_dis = SPDistance.at(cur_idx);
            in_queue.erase(cur_idx);
            std::vector<int> Neighbors = graph->GetNeighbors(cur_idx);
            for (const auto new_idx : Neighbors){
                TValue new_dis = SPDistance.at(cur_idx) + graph->GetWeight(cur_idx, new_idx);
                if (SPDistance.count(new_idx) && SPDistance.at(new_idx) <= new_dis)
                    continue;
                if (SPDistance.count(new_idx) == 0)
                    SPDistance.emplace(new_idx, new_dis);
                else
                    SPDistance.at(new_idx) = new_dis;
                if (!SPPath.count(new_idx)) SPPath.emplace(new_idx, std::vector<int>{});
                SPPath[new_idx] = SPPath[cur_idx];
                SPPath[new_idx].emplace_back(new_idx);
                if (!in_queue.count(new_idx)){
                    q.push(new_idx);
                    in_queue_times[new_idx]++;
                    in_queue.emplace(new_idx);
                }
            }
        }


    }
};

#endif //GRAPHLIBRARY_BELLMANFORDSHORTESTPATHS_H
*/