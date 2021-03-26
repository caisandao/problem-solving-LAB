#include <DataStructures/Edge.h>

Edge::Edge(int s, int d) {
    source = s;
    destination = d;
}

Edge::~Edge() = default;

int Edge::GetSource() const {
    return source;
}

int Edge::GetDestination() const {
    return destination;
}

/*
bool Edge::SameEdge(Edge e) const {
    return (e.GetSource() == source && e.GetDestination() == destination);
}
 */