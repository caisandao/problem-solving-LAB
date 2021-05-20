//
// Created by ASUS on 2021/5/19.
//

#ifndef GRAPHLIBRARY_FLOYDSHORTESTPATHS_H
#define GRAPHLIBRARY_FLOYDSHORTESTPATHS_H

#include <Algorithms/MultiSourceShortestPaths.h>
#include <DataStructures/WeightedEdge.h>
#include <vector>
#include <unordered_map>

template <typename TGraph>
class FloydShortestPaths : public MultiSourceShortestPaths<TGraph> {
private:
    std::vector<std::vector<bool>> vis;
    std::vector<std::vector<typename TGraph::value_type>> dis;
    std::vector<std::vector<int>> paths;
    std::unordered_map<int, int> vertices; // key is the true vertex, value is the number
    std::unordered_map<int, int> vertices_inverse; // key is the number, value is the true vertex
    std::vector<std::vector<bool>> o_edges;
public:
    FloydShortestPaths(const TGraph *graph) : MultiSourceShortestPaths<TGraph>(graph) {
        // initialization of vis and dis
        std::vector<int> v = graph->GetVertices();
        for (int i = 0; i < v.size(); i++) {
            vertices.insert(std::make_pair(v[i], i));
        }
        std::vector<typename TGraph::value_type> tmp;
        std::vector<bool> tmp_vis;
        for (int i = 0; i < v.size(); i++) {
            tmp.emplace_back(typename TGraph::value_type());
            tmp_vis.emplace_back(false);
        }
        for (int i = 0; i < v.size(); i++) {
            dis[i].emplace_back(tmp);
            vis[i].emplace_back(tmp_vis);
            o_edges.emplace_back(tmp_vis);
        }
        /*
        for (int i = 0; i < v.size(); i++) {
            std::vector<WeightedEdge<typename TGraph::value_type>> out_edge = graph->GetOutgoingEdges(v[i]);
            for (auto & we : out_edge) {
                dis[i][vertices[we.GetDestination()]] = we.GetWeight();
                vis[i][vertices[we.GetDestination()]] = true;
                o_edges[i][vertices[we.GetDestination()]] = true;
            }
        }

        // initialization of paths
        std::vector<int> tmp_path;
        for (int i = 0; i < v.size(); i++) {
            tmp_path.emplace_back(i);
        }
        for (int i = 0; i < v.size(); i++) {
            paths.emplace_back(tmp_path);
        }

        // relax
        for (int i = 0; i < v.size(); i++) {
            for (int k = 0; k < v.size(); k++) {
                for (int j = 0; j < v.size(); j++) {
                    if (vis[i][k] && vis[k][j] && !vis[i][j]) {
                        if (o_edges[i][k] && paths[i][k] == k) {
                            dis[i][j] = dis[k][j] + dis[i][k];
                        } else if (o_edges[k][j] && paths[k][j] == j) {
                            dis[i][j] = dis[i][k] + dis[k][j];
                        } else {
                            dis[i][j] = dis[i][k] + dis[k][j]; // 这里需要左结合和右结合进行区别，看看这来这两个里面有无edge，可以找个东西存一下
                        }
                        vis[i][j] = true;
                    } else if (vis[i][k] && vis[k][j] && vis[i][j] && dis[i][j] > dis[i][k] + dis[k][j]) {
                        if (o_edges[i][k] && paths[i][k] == k) {
                            dis[i][j] = dis[k][j] + dis[i][k];
                        } else if (o_edges[k][j] && paths[k][j] == j) {
                            dis[i][j] = dis[i][k] + dis[k][j];
                        } else {
                            dis[i][j] = dis[i][k] + dis[k][j]; // 这里需要左结合和右结合进行区别，看看这来这两个里面有无edge，可以找个东西存一下
                        }
                        vis[i][j] = true;
                    } else {
                        continue;
                    }
                }
            }
        }
        */
    };

    ~FloydShortestPaths() {
        vis.clear();
        dis.clear();
        paths.clear();
        vertices.clear();
        vertices_inverse.clear();
    };
    bool HasPathTo(int source, int destination) const {
        if (!this->graph->ContainsVertex(source) || !this->graph->ContainsVertex(destination))
            return false;
        if (vis[vertices.at(source)][vertices.at(destination)])
            return true;
        else
            return false;
    };
    std::optional<typename TGraph::value_type> TryGetDistanceTo(int source, int destination) const {
        if (!HasPathTo(source, destination))
            return std::nullopt;
        else {
            return dis[vertices.at(source)][vertices.at(destination)];
        }
    };
    std::optional<std::vector<int>> TryGetShortestPathTo(int source, int destination) const {
        if (!HasPathTo(source, destination))
            return std::nullopt;
        else {
            std::vector<int> tmp;
            if (source == destination) {
                tmp.emplace_back(source);
                tmp.emplace_back(destination);
                return tmp;
            } else {
                int sou_num = vertices.at(source);
                int des_num = vertices.at(destination);
                int pt = paths[sou_num][des_num];
                tmp.emplace_back(destination);
                while (pt != sou_num) {
                    tmp.emplace_back(vertices_inverse.at(pt));
                    pt = paths[sou_num][pt];
                }
                tmp.emplace_back(source);
                std::vector<int> tmp2;
                for (int i = tmp.size() - 1; i >= 0; i++) {
                    tmp2.emplace_back(tmp[i]);
                }
                return tmp2;
            }
        }
    };
};

#endif //GRAPHLIBRARY_FLOYDSHORTESTPATHS_H
