//
// Created by ASUS on 2021/3/13.
//


#include <cassert>
#include <DataStructures/WeightedGraph.h>
#include <iostream>
using namespace std;

int main() {
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
    assert(wg.AddEdge(1, 3, 4) == true);
    assert(wg.AddEdge(2, 5, 5) == false);
    assert(wg.ContainsEdge(1, 2) == true);
    assert(wg.ContainsEdge(2, 5) == false);
    //***********
    assert(wg.AddEdge(2, 3, 6) == true);
    assert(wg.RemoveEdge(2, 3) == true);
    assert(wg.CountVertices() == 3);
    assert(wg.CountEdges() == 2);
    assert(wg.GetVertices().size() == 3);
    assert(wg.GetEdges().size() == 2);
    assert(wg.AddVertex(2147483647));
    assert(wg.RemoveVertex(2147483647));
    //**********

    assert(wg.GetDegree(1) == 2);
    assert(wg.GetIncomingEdges(1).empty());
    assert(wg.GetOutgoingEdges(1).size() == 2);
    assert(wg.GetNeighbors(1).size() == 2);
    assert(wg.GetNeighbors(2).empty());
}
