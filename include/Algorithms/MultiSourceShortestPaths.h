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
  virtual bool HasPathOf(int source, int destination) const = 0;
  virtual std::optional<typename TGraph::value_type> TryGetDistanceOf(int source, int destination) const = 0;
  virtual std::optional<std::vector<int>> TryGetShortestPathOf(int source, int destination) const = 0;
};
#endif
