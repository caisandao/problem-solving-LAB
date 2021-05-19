#ifndef SHORTEST_PATHS
#define SHORTEST_PATHS

#include <vector>
#include <optional>

//template <template<typename> class TGraph, typename TValue>
template<typename TGraph>
class ShortestPaths {
protected:
    typedef typename TGraph::value_type TValue;
    const TGraph *graph;
    int source;
public:
  ShortestPaths() = delete; // 显式禁用没有参数的构造函数
  ShortestPaths(const TGraph *graph, int source) {
      this->graph = graph;
      this->source = source;
  };
  virtual ~ShortestPaths() {

  };
public:
  virtual bool HasPathTo(int destination) const = 0;
  virtual std::optional<TValue> TryGetDistanceTo(int destination) const = 0;
  virtual std::optional<std::vector<int>> TryGetShortestPathTo(int destination) const = 0;
};

#endif
