/*
#ifndef MULTI_SOURCE_SHORTEST_PATHS
#define MULTI_SOURCE_SHORTEST_PATHS

#include <vector>
#include <map>
#include <optional>

template <typename TGraph>
class MultiSourceShortestPaths {
protected:
    const TGraph *graph;
    typedef typename TGraph::value_type TValue;
    std::map<std::pair<int, int>, TValue> dis;
    std::map<std::pair<int, int>, std::vector<int>> paths;
    std::vector<int> vertices;
public:
  MultiSourceShortestPaths() = delete;
  explicit MultiSourceShortestPaths(const TGraph *graph) {
      this->graph = graph;
      vertices = graph->GetVertices();
      for (auto & vertex : vertices) {
          dis.emplace(std::make_pair(vertex, vertex), TValue());
          paths.emplace(std::make_pair(vertex, vertex), std::vector<int>{vertex});
      }
      for (auto & vertex : vertices) {
          std::vector<int> tmp = graph->GetNeighbors(vertex);
          for (auto & des : tmp) {
              dis.emplace(std::make_pair(vertex, des), graph->GetWeight(vertex, des));
              paths.emplace(std::make_pair(vertex, des), std::vector<int>{vertex});
          }
      }
  };
  virtual ~MultiSourceShortestPaths() {
      dis.clear();
      paths.clear();
      vertices.clear();
  };
public:
  virtual bool HasPathTo(int source, int destination) const = 0;
  virtual std::optional<typename TGraph::value_type> TryGetDistanceTo(int source, int destination) const = 0;
  virtual std::optional<std::vector<int>> TryGetShortestPathTo(int source, int destination) const = 0;
};

#endif
*/

#ifndef MULTI_SOURCE_SHORTEST_PATHS
#define MULTI_SOURCE_SHORTEST_PATHS

#include <vector>
#include <optional>
#include <DataStructures/WeightedEdge.h>

template<typename TGraph>
class MultiSourceShortestPaths {
public:
    typedef typename TGraph::value_type TValue;

protected:
    std::map<std::pair<int, int>, TValue> Distance;
    std::map<std::pair<int, int>, std::vector<int>> Path;
    std::vector<int> vertices;
public:
    MultiSourceShortestPaths() = delete;

    explicit MultiSourceShortestPaths(const TGraph *graph) {
        vertices = graph->GetVertices();
        for (int src : vertices) {
            Distance.emplace(std::make_pair(src, src), TValue());
            Path.emplace(std::make_pair(src, src), std::vector<int>{src});
            for (const int dst : graph->GetNeighbors(src))
                Distance.emplace(std::make_pair(src, dst), graph->GetWeight(src, dst));
        }
    }

    virtual ~MultiSourceShortestPaths() {
        Distance.clear();
        Path.clear();
        vertices.clear();
    }

public:
    [[nodiscard]] bool HasPathTo(int source, int destination) const {
        if (std::find(vertices.begin(), vertices.end(), source) == vertices.end())
            return false;
        if (std::find(vertices.begin(), vertices.end(), destination) == vertices.end())
            return false;
        return Distance.count(std::make_pair(source, destination)) == 1;
    }

    std::optional<TValue> TryGetDistanceTo(int source, int destination) const {
        if (HasPathTo(source, destination))
            return Distance.at(std::make_pair(source, destination));
        return std::nullopt;
    }

    [[nodiscard]] std::optional<std::vector<int>> TryGetShortestPathTo(int source, int destination) const {
        if (!HasPathTo(source, destination))
            return std::nullopt;
        return Path.at(std::make_pair(source, destination));
    }
};


#endif