//
// Created by ASUS on 2021/3/13.
//

#ifndef GRAPHLIBRARY_WEIGHTEDEDGE_H
#define GRAPHLIBRARY_WEIGHTEDEDGE_H

#include <DataStructures/Edge.h>

template <typename T>
class WeightedEdge {
public:
    WeightedEdge(int v1, int v2, T w) {
        source = v1;
        destination = v2;
        weight = w;
    };
    ~WeightedEdge() = default;
public:
    T GetWeight() const {
        return weight;
    };
    int GetSource() const {
        return source;
    };
    int GetDestination() const {
        return destination;
    };
private:
    int source;
    int destination;
    T weight;
};

#endif //GRAPHLIBRARY_WEIGHTEDEDGE_H
