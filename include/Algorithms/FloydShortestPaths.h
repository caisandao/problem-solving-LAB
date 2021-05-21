//
// Created by ASUS on 2021/5/19.
//
#ifndef CHECK
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
                if (i == j) continue;
                if (paths.count({i, j}))
                    paths[{i, j}].emplace_back(j);
            }
        }
    };

    ~FloydShortestPaths() = default;

    bool HasPathTo(int source, int destination) const {
        if (!graph1->ContainsVertex(source) || !graph1->ContainsVertex(destination)) return false;
        if (dis.count({source, destination})) return true;
        else return false;
    };

    std::optional<typename TGraph::value_type> TryGetDistanceTo(int source, int destination) const {
        if (HasPathTo(source, destination))
            return dis.at({source, destination});
        else
            return std::nullopt;
    };

    std::optional<std::vector<int>> TryGetShortestPathTo(int source, int destination) const {
        if (HasPathTo(source, destination))
            return paths.at({source, destination});
        else
            return std::nullopt;
    };
};

#endif //GRAPHLIBRARY_FLOYDSHORTESTPATHS_H
#endif

#ifdef CHECK
#ifndef GRAPHLIBRARY_FLOYDSHORTESTPATHS_H
#define GRAPHLIBRARY_FLOYDSHORTESTPATHS_H

#include "Algorithms/MultiSourceShortestPaths.h"
//#include "Exceptions/NegativeCycleException.h"
#define vertices MultiSourceShortestPaths<TGraph>::vertices
#define Distance MultiSourceShortestPaths<TGraph>::Distance
#define Path     MultiSourceShortestPaths<TGraph>::Path

template<typename TGraph>
class FloydShortestPaths : public MultiSourceShortestPaths<TGraph>{
public:
    typedef typename TGraph::value_type TValue;
public:
    explicit FloydShortestPaths(const TGraph *graph) : MultiSourceShortestPaths<TGraph>(graph){
        std::map<std::pair<int, int>, int> mid;
//        return ;

        for (int k : vertices)
            for (int i : vertices) {
//                if (i == k) continue;
                for (int j : vertices) {
//                    if (j == i || j == k)   continue;
                    if (!Distance.count({i, k})|| !Distance.count({k, j}))
                        continue;
                    TValue new_dis = Distance.at({i, k}) + Distance.at({k, j});
                    if (Distance.count({i, j}) == 1 && Distance.at({i, j}) <= new_dis)
                        continue;
                    Distance[{i, j}] = new_dis;
                    if (mid.count({k, j}) == 1)
                        mid[{i, j}]= mid[{k, j}];
                    else
                        mid[{i, j}] = k;
                }

            }

//        printf("suc\n");

        for (int src : vertices)
            for (int dst : vertices){
                if (src == dst) continue;
                if (!Distance.count({src, dst}))  continue;
                Path[{src, dst}].insert(Path[{src, dst}].begin(), dst);
                int tmp = dst;
                while(mid.count({src, tmp}) == 1) {
                    tmp = mid[{src, tmp}];
                    Path[{src, dst}].insert(Path[{src, dst}].begin(), tmp);
                }
                Path[{src, dst}].insert(Path[{src, dst}].begin(), src);
            }

    }

    ~FloydShortestPaths() = default;
};

#endif //GRAPHLIBRARY_FLOYDSHORTESTPATHS_H
#endif