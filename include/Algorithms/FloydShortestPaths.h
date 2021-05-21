//
// Created by ASUS on 2021/5/19.
//

#ifndef GRAPHLIBRARY_FLOYDSHORTESTPATHS_H
#define GRAPHLIBRARY_FLOYDSHORTESTPATHS_H

#include <Algorithms/MultiSourceShortestPaths.h>
//#define g MultiSourceShortestPaths<TGraph>::graph
#define vertices MultiSourceShortestPaths<TGraph>::vertices
#define dis MultiSourceShortestPaths<TGraph>::dis
#define paths MultiSourceShortestPaths<TGraph>::paths

template <typename TGraph>
class FloydShortestPaths : public MultiSourceShortestPaths<TGraph> {
private:
    std::vector<int> add_paths(std::vector<int> p1, std::vector<int> p2) {
        std::vector<int> ret = p1;
        for (auto & i : p2) {
            ret.emplace_back(i);
        }
        return ret;
    };
public:
    explicit FloydShortestPaths(const TGraph *graph) : MultiSourceShortestPaths<TGraph>(graph) {
        for (auto & i : vertices) {
            for (auto & k : vertices) {
                for (auto & j : vertices) {
                    if (dis.count({i, k}) &&
                        dis.count({k, j}) &&
                        (!dis.count({i, j}) || dis[{i, j}] > dis[{i, k}] + dis[{k, j}])) {
                        dis[{i, j}] = dis[{i, k}] + dis[{k, j}];
                        paths[{i, j}] = add_paths(paths[{i, k}], paths[{k, j}]);
                    }
                }
            }
        }
        for (auto & i : vertices) {
            for (auto & j : vertices) {
                if (paths.count({i, j}))
                    paths[{i, j}].emplace_back(j);
            }
        }
    };

    ~FloydShortestPaths() = default;

    bool HasPathTo(int source, int destination) const {
        //if (!g->ContainsVertex(source) || !g->ContainsVertex(destination)) return false;
        if (dis.count({source, destination})) return true;
        else return false;
    };

    std::optional<typename TGraph::value_type> TryGetDistanceTo(int source, int destination) const {
        if (HasPathTo(source, destination))
            return dis[{source, destination}];
        else
            return std::nullopt;
    };

    std::optional<std::vector<int>> TryGetShortestPathTo(int source, int destination) const {
        if (HasPathTo(source, destination))
            return paths[{source, destination}];
        else
            return std::nullopt;
    };
};

#endif //GRAPHLIBRARY_FLOYDSHORTESTPATHS_H
