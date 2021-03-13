//
// Created by ASUS on 2021/3/13.
//

#ifndef GRAPHLIBRARY_WEIGHTEDEDGE_H
#define GRAPHLIBRARY_WEIGHTEDEDGE_H

#include <DataStructures/Edge.h>

class WeightedEdge : public Edge {
public:
    WeightedEdge(int v1, int v2, int w) : Edge(v1, v2) {weight = w;};
    ~WeightedEdge();
public:
    int GetWeight() const;
private:
    int weight;
};

#endif //GRAPHLIBRARY_WEIGHTEDEDGE_H
