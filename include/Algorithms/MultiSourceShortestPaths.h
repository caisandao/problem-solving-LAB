#ifndef MULTI_SOURCE_SHORTEST_PATHS
#define MULTI_SOURCE_SHORTEST_PATHS

#include <vector>
#include <optional>

template <typename TGraph>
class MultiSourceShortestPaths {
protected:
    const TGraph *graph;
public:
  MultiSourceShortestPaths() = delete;
  explicit MultiSourceShortestPaths(const TGraph *graph) {
      this->graph = graph;
  };
  virtual ~MultiSourceShortestPaths() = default;
public:
  virtual bool HasPathTo(int source, int destination) const = 0;
  virtual std::optional<typename TGraph::value_type> TryGetDistanceTo(int source, int destination) const = 0;
  virtual std::optional<std::vector<int>> TryGetShortestPathTo(int source, int destination) const = 0;
};

#endif
