
#include <cassert>
#include <DataStructures/Graph.h>
#include <iostream>
#include <DataStructures/UndirectedGraph.h>
#include <DataStructures/UndirectedWeightedGraph.h>
#include <Algorithms/DepthFirstSearcher.h>
#include <Algorithms/ShortestPaths.h>
#include <Algorithms/DijkstraShortestPaths.h>
#include <Algorithms/BellmanFordShortestPaths.h>
using namespace std;

int main() {
  Graph g;

  /*
   * bool AddVertex(int vertex); *
    bool RemoveVertex(int vertex); *
    bool AddEdge(int vertex1, int vertex2, int weight); *
    bool RemoveEdge(int vertex1, int vertex2); *
    int CountVertices() const; *
    int CountEdges() const;  *
    bool ContainsVertex(int vertex) const; *
    bool ContainsEdge(int vertex1, int vertex2) const; *
    int GetWeight(int vertex1, int vertex2) const; *
    std::vector<int> GetVertices() const; *
    std::vector<WeightedEdge> GetEdges() const; *
    std::vector<WeightedEdge> GetIncomingEdges(int vertex) const; *
    std::vector<WeightedEdge> GetOutgoingEdges(int vertex) const; *
    int GetDegree(int vertex) const; *
    std::vector<int> GetNeighbors(int vertex) const; *
   */
  /*
  assert(g.AddVertex(1) == true);
  assert(g.AddVertex(2) == true);
  assert(g.AddVertex(3) == true);
  assert(g.AddVertex(4) == true);
  assert(g.AddVertex(5) == true);
  assert(g.AddVertex(6) == true);
  assert(g.AddVertex(7) == true);
  assert(g.AddEdge(1, 2) == true);
  assert(g.AddEdge(2, 3) == true);
  assert(g.AddEdge(3, 4) == true);
  assert(g.AddEdge(4, 5) == true);
  assert(g.AddEdge(5, 6) == true);
  assert(g.AddEdge(6, 7) == true);
  assert(g.AddEdge(7, 1) == true);
  assert(g.AddEdge(7, 2) == true);
  assert(g.AddEdge(7, 3) == true);
  assert(g.AddEdge(7, 4) == true);
  assert(g.AddEdge(7, 5) == true);
  assert(g.AddEdge(7, 6) == true);
  assert(g.AddEdge(7, 7) == true);
  assert(g.GetOutgoingEdges(7).size() == 7);
  */


  assert(g.AddVertex(1) == true);
  assert(g.AddVertex(2) == true);
  assert(g.AddVertex(3) == true);
  assert(g.AddVertex(3) == false);
  assert(g.AddVertex(4) == true);
  assert(g.CountVertices() == 4);
  assert(g.GetVertices().size() == 4);
  assert(g.ContainsVertex(4) == true);
  assert(g.ContainsVertex(2) == true);
  assert(g.RemoveVertex(4) == true);
  assert(g.GetVertices().size() == 3);
  assert(g.CountVertices() == 3);
  assert(g.ContainsVertex(4) == false);
  assert(g.RemoveVertex(5) == false);

  assert(g.AddEdge(1, 2) == true);
  assert(g.AddEdge(1, 2) == false);
  assert(g.GetWeight(1, 2) == 1);
  assert(g.AddEdge(1, 3) == true);
  assert(g.AddEdge(2, 5) == false);
  assert(g.ContainsEdge(1, 2) == true);
  assert(g.ContainsEdge(2, 5) == false);


  assert(g.AddEdge(2, 3) == true);
  assert(g.GetEdges().size() == 3);
  assert(g.ContainsEdge(2, 3) == true);
  assert(g.CountEdges() == 3);
  assert(g.RemoveEdge(2, 3) == true);
  assert(g.GetEdges().size() == 2);
  assert(g.CountEdges() == 2);
  assert(g.RemoveEdge(2, 5) == false);
  assert(g.ContainsEdge(2, 3) == false);
  assert(g.CountVertices() == 3);
  assert(g.CountEdges() == 2);
  assert(g.GetVertices().size() == 3);
  assert(g.GetEdges().size() == 2);
  assert(g.AddVertex(2147483647));
  assert(g.RemoveVertex(2147483647));


  assert(g.GetDegree(1) == 2);
  assert(g.GetDegree(2) == 0);
  assert(g.GetDegree(3) == 0);
  assert(g.GetIncomingEdges(1).empty());
  assert(g.GetOutgoingEdges(1).size() == 2);
    assert(g.GetOutgoingEdges(1)[0].GetSource() == 1);
    assert(g.GetOutgoingEdges(1)[0].GetDestination() == 2);
    assert(g.GetOutgoingEdges(1)[1].GetSource() == 1);
    assert(g.GetOutgoingEdges(1)[1].GetDestination() == 3);
    assert(g.GetIncomingEdges(2).size() == 1);
    assert(g.GetIncomingEdges(2)[0].GetSource() == 1);
    assert(g.GetIncomingEdges(2)[0].GetDestination() == 2);
  assert(g.GetNeighbors(1).size() == 2);
  assert(g.GetNeighbors(2).empty());
  assert(g.GetOutgoingEdges(1).size() == 2);

  assert(g.GetWeight(1, 2) == 1);

  assert(g.AddVertex(4));
  assert(g.AddVertex(5));
  assert(g.AddEdge(4, 5));
  assert(g.GetNeighbors(4)[0] == 5);
  assert(g.GetNeighbors(6).empty());

  WeightedGraph<int> wg;

  assert(wg.AddVertex(1) == true);
  assert(wg.AddVertex(2) == true);
  assert(wg.AddVertex(3) == true);
  assert(wg.AddEdge(1, 2, 3) == true);
  assert(wg.AddEdge(1, 3, 3) == true);
  assert(wg.GetOutgoingEdges(1).size() == 2);
  assert(wg.GetOutgoingEdges(2).empty());
  assert(wg.AddVertex(4) == true);
  assert(wg.AddVertex(5) == true);
  assert(wg.AddEdge(4, 5, 3) == true);
  assert(wg.GetOutgoingEdges(4)[0].GetWeight() == 3);
  assert(wg.GetOutgoingEdges(4)[0].GetSource() == 4);
  assert(wg.GetOutgoingEdges(4)[0].GetDestination() == 5);
  assert(wg.GetOutgoingEdges(1).size() == 2);
  assert(wg.GetIncomingEdges(2).size() == 1);
  assert(wg.GetIncomingEdges(2)[0].GetWeight() == 3);
  assert(wg.GetIncomingEdges(2)[0].GetSource() == 1);
  assert(wg.GetIncomingEdges(2)[0].GetDestination() == 2);
  assert(wg.GetEdges().size() == 3);
  assert(wg.AddVertex(6) == true);
  assert(wg.AddVertex(7) == true);
  assert(wg.AddEdge(6, 7, 3) == true);
  assert(wg.GetEdges().size() == 4);
  assert(wg.RemoveEdge(6, 7) == true);
  assert(wg.GetEdges().size() == 3);


  // 测试无向图
  UndirectedGraph ug;
  assert(ug.AddVertex(1) == true);
  assert(ug.AddVertex(2) == true);
  assert(ug.AddEdge(1, 2) == true);
  assert(ug.RemoveEdge(1, 2) == true);
  assert(ug.RemoveEdge(1, 2) == false);
  assert(ug.AddVertex(3) == true);
  assert(ug.AddEdge(1, 2) == true);
  assert(ug.AddEdge(1, 3) == true);
  assert(ug.CountEdges() == 2);
  assert(ug.ContainsEdge(1, 2) == true);
  assert(ug.ContainsEdge(2, 3) == false);
  assert(ug.AddEdge(1, 1) == true);
  assert(ug.CountEdges() == 3);
  assert(ug.AddEdge(1, 2) == false);
  assert(ug.CountEdges() == 3);
  assert(ug.ContainsEdge(1, 1) == true);
  assert(ug.RemoveEdge(1, 1) == true);
  assert(ug.CountEdges() == 2);
  assert(ug.ContainsEdge(1, 1) ==false);
  assert(ug.AddEdge(4, 5) == false);
  assert(ug.RemoveEdge(4, 5) == false);

  UndirectedWeightedGraph<int> uwg;
  assert(uwg.AddVertex(1) == true);
  assert(uwg.AddVertex(2) == true);
  assert(uwg.AddEdge(1, 2, 3) == true);
  assert(uwg.GetWeight(1, 2) == 3);
  assert(uwg.RemoveEdge(1, 2) == true);
  assert(uwg.RemoveEdge(1, 2) == false);
  assert(uwg.AddVertex(3) == true);
  assert(uwg.AddEdge(1, 2, 3) == true);
  assert(uwg.AddEdge(1, 3, 3) == true);
  assert(uwg.CountEdges() == 2);
  assert(uwg.ContainsEdge(1, 2) == true);
  assert(uwg.ContainsEdge(2, 3) == false);
  assert(uwg.AddEdge(1, 1, 3) == true);
  assert(uwg.CountEdges() == 3);
  assert(uwg.AddEdge(1, 2, 3) == false);
  assert(uwg.CountEdges() == 3);
  assert(uwg.ContainsEdge(1, 1) == true);
  assert(uwg.RemoveEdge(1, 1) == true);
  assert(uwg.CountEdges() == 2);
  assert(uwg.ContainsEdge(1, 1) ==false);
  assert(uwg.AddEdge(4, 5, 3) == false);
  assert(uwg.RemoveEdge(4, 5) == false);

  UndirectedWeightedGraph<double> uwg2;
    assert(uwg2.AddVertex(1) == true);
    assert(uwg2.AddVertex(2) == true);
    assert(uwg2.AddEdge(1, 2, 3.2) == true);
    assert(uwg2.GetWeight(1, 2) == 3.2);
    assert(uwg2.RemoveEdge(1, 2) == true);
    assert(uwg2.RemoveEdge(1, 2) == false);
    assert(uwg2.AddVertex(3) == true);
    assert(uwg2.AddEdge(1, 2, 3.5) == true);
    assert(uwg2.AddEdge(1, 3, 3.6) == true);
    assert(uwg2.CountEdges() == 2);
    assert(uwg2.ContainsEdge(1, 2) == true);
    assert(uwg2.ContainsEdge(2, 3) == false);
    assert(uwg2.AddEdge(1, 1, 2.2) == true);
    assert(uwg2.CountEdges() == 3);
    assert(uwg2.AddEdge(1, 2, 3.5) == false);
    assert(uwg2.CountEdges() == 3);
    assert(uwg2.ContainsEdge(1, 1) == true);
    assert(uwg2.RemoveEdge(1, 1) == true);
    assert(uwg2.CountEdges() == 2);
    assert(uwg2.ContainsEdge(1, 1) ==false);
    assert(uwg2.AddEdge(4, 5, 3.7) == false);
    assert(uwg2.RemoveEdge(4, 5) == false);

    WeightedGraph<double> wg2;

    assert(wg2.AddVertex(1) == true);
    assert(wg2.AddVertex(2) == true);
    assert(wg2.AddVertex(3) == true);
    assert(wg2.AddEdge(1, 2, 3.6) == true);
    assert(wg2.AddEdge(1, 3, 3.7) == true);
    assert(wg2.GetWeight(1, 2) == 3.6);
    assert(wg2.GetOutgoingEdges(1).size() == 2);
    assert(wg2.GetOutgoingEdges(2).empty());
    assert(wg2.AddVertex(4) == true);
    assert(wg2.AddVertex(5) == true);
    assert(wg2.AddEdge(4, 5, 3.4) == true);
    assert(wg2.GetOutgoingEdges(4)[0].GetWeight() == 3.4);
    assert(wg2.GetOutgoingEdges(4)[0].GetSource() == 4);
    assert(wg2.GetOutgoingEdges(4)[0].GetDestination() == 5);
    assert(wg2.GetOutgoingEdges(1).size() == 2);
    assert(wg2.GetIncomingEdges(2).size() == 1);
    assert(wg2.GetIncomingEdges(2)[0].GetWeight() == 3.6);
    assert(wg2.GetIncomingEdges(2)[0].GetSource() == 1);
    assert(wg2.GetIncomingEdges(2)[0].GetDestination() == 2);
    assert(wg2.GetEdges().size() == 3);
    assert(wg2.AddVertex(6) == true);
    assert(wg2.AddVertex(7) == true);
    assert(wg2.AddEdge(6, 7, 3) == true);
    assert(wg2.GetEdges().size() == 4);
    assert(wg2.RemoveEdge(6, 7) == true);
    assert(wg2.GetEdges().size() == 3);

    auto *wg_a = new WeightedGraph<int>();
    assert(wg_a->AddVertex(1) == true);
    assert(wg_a->AddVertex(2) == true);
    assert(wg_a->AddVertex(3) == true);
    assert(wg_a->AddVertex(4) == true);
    assert(wg_a->AddVertex(5) == true);
    assert(wg_a->AddEdge(1, 2, 3) == true);
    assert(wg_a->AddEdge(1, 3, 3) == true);
    assert(wg_a->AddEdge(1, 4, 3) == true);
    assert(wg_a->AddEdge(3, 4, 3) == true);
    assert(wg_a->AddEdge(3, 5, 3) == true);
    DepthFirstSearcher<WeightedGraph<int>>::VisitAllVertices(wg_a, 1, [](int u)->void{printf("%d", u);});

    WeightedGraph<int> wg_for_dij;
    assert(wg_for_dij.AddVertex(1));
    assert(wg_for_dij.AddVertex(2));
    assert(wg_for_dij.AddVertex(3));
    assert(wg_for_dij.AddVertex(4));
    assert(wg_for_dij.AddVertex(5));
    assert(wg_for_dij.AddEdge(1, 2, 1));
    assert(wg_for_dij.AddEdge(1, 5, 4));
    assert(wg_for_dij.AddEdge(1, 3, 2));
    assert(wg_for_dij.AddEdge(2, 5, 2));
    assert(wg_for_dij.AddEdge(5, 4, 1));
    assert(wg_for_dij.AddEdge(3, 4, 3));

    DijkstraShortestPaths<WeightedGraph<int>> ds(&wg_for_dij, 1);
    assert(ds.HasPathTo(2));
    assert(ds.HasPathTo(3));
    assert(ds.HasPathTo(4));
    assert(ds.HasPathTo(5));
    assert(ds.TryGetDistanceTo(2) == 1);
    assert(ds.TryGetDistanceTo(3) == 2);
    assert(ds.TryGetDistanceTo(4) == 4);
    assert(ds.TryGetDistanceTo(5) == 3);
    vector<int> tmp;
    tmp.emplace_back(1);
    tmp.emplace_back(2);
    tmp.emplace_back(5);
    assert(ds.TryGetShortestPathTo(5) == tmp);

    WeightedGraph<int> wg_for_bij;
    assert(wg_for_bij.AddVertex(1));
    assert(wg_for_bij.AddVertex(2));
    assert(wg_for_bij.AddVertex(3));
    assert(wg_for_bij.AddVertex(4));
    assert(wg_for_bij.AddVertex(5));
    assert(wg_for_bij.AddEdge(1, 2, 1));
    assert(wg_for_bij.AddEdge(1, 5, 4));
    assert(wg_for_bij.AddEdge(1, 3, 2));
    assert(wg_for_bij.AddEdge(2, 5, 2));
    assert(wg_for_bij.AddEdge(5, 4, 1));
    assert(wg_for_bij.AddEdge(3, 4, 3));
    BellmanFordShortestPaths<WeightedGraph<int>> bs(&wg_for_bij, 1);
    assert(bs.HasPathTo(2));
    assert(bs.HasPathTo(3));
    assert(bs.HasPathTo(4));
    assert(bs.HasPathTo(5));
    assert(bs.TryGetDistanceTo(2) == 1);
    assert(bs.TryGetDistanceTo(3) == 2);
    assert(bs.TryGetDistanceTo(4) == 4);
    assert(bs.TryGetDistanceTo(5) == 3);
    vector<int> tmp2;
    tmp2.emplace_back(1);
    tmp2.emplace_back(2);
    tmp2.emplace_back(5);
    assert(bs.TryGetShortestPathTo(5) == tmp2);

}

/*
int main() {

    Graph g;
    WeightedGraph wg;

    assert(wg.AddVertex(1) == true);
    assert(wg.AddVertex(2) == true);
    assert(wg.AddVertex(3) == true);
    assert(wg.AddVertex(3) == false);
    assert(wg.AddVertex(4) == true);


    assert(wg.ContainsVertex(4) == true);
    assert(wg.RemoveVertex(4) == true);
    assert(wg.ContainsVertex(4) == false);
    assert(wg.RemoveVertex(5) == false);

    assert(wg.AddEdge(1, 2, 3) == true);
    assert(wg.AddEdge(1, 3, 3) == true);
    assert(wg.AddEdge(2, 5, 3) == false);
    assert(wg.ContainsEdge(1, 2) == true);
    assert(wg.ContainsEdge(2, 5) == false);

    assert(wg.GetDegree(1) == 2);
    assert(wg.GetIncomingEdges(1).empty());
    assert(wg.GetOutgoingEdges(1).size() == 2);
    assert(wg.GetNeighbors(1).size() == 2);
    assert(wg.GetNeighbors(2).empty());

    assert(wg.RemoveEdge(1,2) == true);
    assert(wg.RemoveEdge(2,3) == false);

    WeightedGraph q;
    for(int i = 0; i < 1000; i++){
      q.AddVertex(i*3);
    }
    assert(q.CountVertices() == 1000);

    for(int i = 0; i < 999; i++){
         assert( q.AddEdge(i*3, (i+1)*3, 112) == true);
    }
     for(int i = 0; i < 999; i++)
        assert(q.ContainsEdge(i * 3, (i + 1) * 3));

      assert(q.CountEdges() == 999);
}
 */