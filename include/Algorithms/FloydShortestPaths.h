//
// Created by ASUS on 2021/5/19.
//

#ifndef GRAPHLIBRARY_FLOYDSHORTESTPATHS_H
#define GRAPHLIBRARY_FLOYDSHORTESTPATHS_H

#include <Algorithms/MultiSourceShortestPaths.h>
#define graph1 MultiSourceShortestPaths<TGraph>::graph
#define vertices MultiSourceShortestPaths<TGraph>::vertices
#define dis MultiSourceShortestPaths<TGraph>::dis
#define paths MultiSourceShortestPaths<TGraph>::paths

template <typename TGraph>
class FloydShortestPaths : public MultiSourceShortestPaths<TGraph> {
private:
    typedef typename TGraph::value_type TValue;
    std::vector<int> add_paths(std::vector<int> p1, std::vector<int> p2) {
        std::vector<int> ret = p1;
        for (auto & i : p2) {
            ret.emplace_back(i);
        }
        return ret;
    };
public:
    explicit FloydShortestPaths(const TGraph *graph) : MultiSourceShortestPaths<TGraph>(graph) {
        for (auto & k : vertices) { // rnm,记住floyd三重循环的顺序
            for (auto & i : vertices) {
                for (auto & j : vertices) {
                    if (dis.count({i, k}) &&
                        dis.count({k, j}) &&
                        (!dis.count({i, j}) || dis[{i, j}] > dis[{i, k}] + dis[{k, j}])) {
                        dis[{i, j}] = dis[{i, k}] + dis[{k, j}];
                        paths[{i, j}] = add_paths(paths[{i, k}], paths[{k, j}]);
                    }
                }
                if (dis[{i, i}] < TValue())
                    throw NegativeCycleException("Floyd");
            }
        }
        for (auto & i : vertices) {
            for (auto & j : vertices) {
                if (i == j) continue;
                if (paths.count({i, j}))
                    paths[{i, j}].emplace_back(j);
            }
        }
    };

    ~FloydShortestPaths() = default;

    bool HasPathOf(int source, int destination) const {
        if (!graph1->ContainsVertex(source) || !graph1->ContainsVertex(destination)) return false;
        if (dis.count({source, destination})) return true;
        else return false;
    };

    std::optional<typename TGraph::value_type> TryGetDistanceOf(int source, int destination) const {
        if (HasPathOf(source, destination))
            return dis.at({source, destination});
        else
            return std::nullopt;
    };

    std::optional<std::vector<int>> TryGetShortestPathOf(int source, int destination) const {
        if (HasPathOf(source, destination))
            return paths.at({source, destination});
        else
            return std::nullopt;
    };
};

#endif //GRAPHLIBRARY_FLOYDSHORTESTPATHS_H

