#ifndef DEPTH_FIRST_SEARCHER
#define DEPTH_FIRST_SEARCHER

#include <functional>
#include <optional>
#include <stack>
#include <vector>
#include <cstring>

template <typename TGraph>
class DepthFirstSearcher {
 public:
  static void VisitAllVertices(const TGraph *graph, int start, const std::function<void(int)> &action) {
      if (!graph->ContainsVertex(start))
          return;

      int vis[graph->CountVertices() + 10];
      memset(vis, 0, sizeof(vis));
      std::stack<int> s;
      s.push(start);
      while (!s.empty()) {
          int tmp = s.top();
          action(tmp);
          s.pop();
          if (!vis[tmp])
              vis[tmp] = 1;
          std::vector<int> neighbors = graph->GetNeighbors(tmp);
          for (int & neighbor : neighbors) {
              if (!vis[neighbor])
                  s.push(neighbor);
          }
      }
  };
  static std::optional<int> FindFirstVertex(const TGraph *graph, int start, const std::function<bool(int)> &predicate) {
      if (!graph->ContainsVertex(start))
          return {};

      int vis[graph->CountVertices() + 10];
      memset(vis, 0, sizeof(vis));
      std::stack<int> s;
      s.push(start);
      while (!s.empty()) {
          int tmp = s.top();
          if (predicate(tmp))
              return tmp;
          s.pop();
          if (!vis[tmp])
              vis[tmp] = 1;
          std::vector<int> neighbors = graph->GetNeighbors(tmp);
          for (int & neighbor : neighbors) {
              if (!vis[neighbor])
                  s.push(neighbor);
          }
      }
      return {};
  };
};

#endif
