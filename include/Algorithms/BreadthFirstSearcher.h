#ifndef BREADTH_FIRST_SEARCHER
#define BREADTH_FIRST_SEARCHER

#include <functional>
#include <optional>
#include <queue>
#include <vector>
#include <cstring>

template <typename TGraph>
class BreadthFirstSearcher {
 public:
  static void VisitAllVertices(const TGraph *graph, int start, const std::function<void(int)> &action) {
        if (!graph->ContainsVertex(start))
            return;

        int vis[graph->CountVertices() + 10];
        memset(vis, 0, sizeof(vis));
        std::queue<int> q;
        q.push(start);
        vis[start] = 1;
        while (!q.empty()) {
            int tmp = q.front();
            action(tmp);
            q.pop();
            std::vector<int> neighbors = graph->GetNeighbors(tmp);
            for (int & neighbor : neighbors) {
                if (!vis[neighbor]) {
                    q.push(neighbor);
                    vis[neighbor] = 1;
                }
            }
        }
  };
  static std::optional<int> TryFindFirstVertex(const TGraph *graph, int start, const std::function<bool(int)> &predicate) {
      if (!graph->ContainsVertex(start))
          return {};

      int vis[graph->CountVertices() + 10];
      memset(vis, 0, sizeof(vis));
      std::queue<int> q;
      q.push(start);
      vis[start] = 1;
      while (!q.empty()) {
          int tmp = q.front();
          if (predicate(tmp))
              return tmp;
          q.pop();
          std::vector<int> neighbors = graph->GetNeighbors(tmp);
          for (int & neighbor : neighbors) {
              if (!vis[neighbor]) {
                  q.push(neighbor);
                  vis[neighbor] = 1;
              }
          }
      }
      return {};
  };
};

#endif
