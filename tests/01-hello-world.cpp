
#include <cassert>
#include <DataStructures/Graph.h>
#include <iostream>
using namespace std;

int main() {
  Graph g;

  assert(g.AddVertex(1) == true);
  assert(g.AddVertex(2) == true);
  assert(g.AddVertex(3) == true);
  assert(g.AddVertex(3) == false);
  assert(g.AddVertex(4) == true);
  assert(g.ContainsVertex(4) == true);
  assert(g.ContainsVertex(2) == true);
  assert(g.RemoveVertex(4) == true);
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
  assert(g.RemoveEdge(2, 3) == true);
  assert(g.ContainsEdge(2, 3) == false);
  assert(g.CountVertices() == 3);
  assert(g.CountEdges() == 2);
  assert(g.GetVertices().size() == 3);
  assert(g.GetEdges().size() == 2);
  assert(g.AddVertex(2147483647));
  assert(g.RemoveVertex(2147483647));


  assert(g.GetDegree(1) == 2);
  assert(g.GetIncomingEdges(1).empty());
  assert(g.GetOutgoingEdges(1).size() == 2);
  assert(g.GetNeighbors(1).size() == 2);
  assert(g.GetNeighbors(2).empty());
  assert(g.GetOutgoingEdges(1).size() == 2);

  assert(g.GetWeight(1, 2) == 1);

  assert(g.AddVertex(4));
  assert(g.AddVertex(5));
  assert(g.AddEdge(4, 5));
  assert(g.GetNeighbors(4)[0] == 5);
  assert(g.GetNeighbors(6).empty());

  WeightedGraph wg;

  assert(wg.AddVertex(1) == true);
  assert(wg.AddVertex(2) == true);
  assert(wg.AddVertex(3) == true);
  assert(wg.AddEdge(1, 2, 3) == true);
  assert(wg.AddEdge(1, 3, 3) == true);
  assert(wg.GetOutgoingEdges(1).size() == 2);
  assert(wg.GetOutgoingEdges(2).empty());
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