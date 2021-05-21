#ifndef GRAPHLIBRARY_BIPARTITEGRAPHMATCHING_H
#define GRAPHLIBRARY_BIPARTITEGRAPHMATCHING_H
#include <unordered_set>
#include <optional>
#include <unordered_map>
#include <vector>

template<typename TGraph>
class BipariteGraphMatching {
private:
    std::unordered_map<int, int> match;
    std::unordered_set<int> used;
    bool find(const TGraph *g, int x) {
        for (auto & y : g->GetNeighbors(x)) {
            if (!used.count(y)) {
                used.emplace(y);
                if (!match.count(y) || find(g, match[y])) {
                    match[x] = y;
                    match[y] = x;
                    return true;
                }
            }
        }
        return false;
    };
public:
    BipariteGraphMatching(const TGraph* g, std::unordered_set<int> left, std::unordered_set<int> right) {
        std::vector<int> vertices = g->GetVertices;
        std::unordered_set<int> vertices_in_g;
        for (auto & i : vertices) {
            vertices_in_g.emplace(i);
        }
        for (auto & i : left) {
            if (right.count(i))
                throw std::invalid_argument("some vertex belongs to both left and right");
        }
        for (auto & i : left) {
            if (!vertices_in_g.count(i))
                throw std::invalid_argument("some vertex in left does not belong to V");
        }
        for (auto & i : right) {
            if (!vertices_in_g.count(i))
                throw std::invalid_argument("some vertex in right does not belong to V");
        }
        for (auto & i : left) {
            for (auto & j : g->GetNeighbors(i)) {
                if (!right.count(j))
                    throw std::invalid_argument("some vertex in left does not connect to some vertex in right");
            }
        }
        for (auto & i : right) {
            for (auto & j : g->GetNeighbors(i)) {
                if (!left.count(j)) {
                    throw std::invalid_argument("some vertex in right does not connect to some vertex in left");
                }
            }
        }
        for (auto & x : left) {
            find(g, x);
            used.clear();
        }
    };
    int SumOfMatches() const {
        return match.size() / 2;
    };
    std::optional<int> FindMatchOf(int idx) const {
        if (!match.count(idx))
            return std::nullopt;
        else
            return match.at(idx);
    };
};

#endif //GRAPHLIBRARY_BIPARTITEGRAPHMATCHING_H
