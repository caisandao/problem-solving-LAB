
#ifndef SHORTEST_PATHS
#define SHORTEST_PATHS

#include <vector>
#include <optional>

//template <template<typename> class TGraph, typename TValue>
template<typename TGraph>
class ShortestPaths {
protected:
    //typedef typename TGraph::value_type TValue;
    const TGraph *graph;
    int source;
    static_assert(std::is_default_constructible<typename TGraph::value_type>::value, "TValue requires default constructor");
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
  virtual std::optional<typename TGraph::value_type> TryGetDistanceTo(int destination) const = 0;
  virtual std::optional<std::vector<int>> TryGetShortestPathTo(int destination) const = 0;
};

#endif


/*
#ifndef SHORTEST_PATHS
#define SHORTEST_PATHS

#include <vector>
#include <optional>

template<typename TGraph>
class ShortestPaths {
public:
    typedef typename TGraph::value_type TValue;

protected:
    std::unordered_map<int, TValue> Distance{};
    std::unordered_map<int, std::vector<int>> Path{};
    static_assert(std::is_default_constructible<TValue>::value, "TValue requires default constructor");
public:
    ShortestPaths() = delete;

    ShortestPaths(const TGraph *graph, int source) {
        if (!graph->ContainsVertex(source)) return;
        Distance.emplace(source, TValue());
        Path.emplace(source, std::vector<int>{source});
    }

    ~ShortestPaths(){
        Distance.clear();
        Path.clear();
    }

public:
    [[nodiscard]] bool HasPathTo(int destination) const{
        return Distance.count(destination) == 1;
    }

    std::optional<TValue> TryGetDistanceTo(int destination) const{
        if(HasPathTo(destination))
            return Distance.at(destination);
        else
            return std::nullopt;
    }

    [[nodiscard]] std::optional<std::vector<int>> TryGetShortestPathTo(int destination) const{
        if (HasPathTo(destination))
            return Path.at(destination);
        else
            return std::nullopt;
    }
};



#endif
*/