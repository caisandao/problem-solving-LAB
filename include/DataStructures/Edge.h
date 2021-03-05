#ifndef EDGE_H
#define EDGE_H

class Edge {
 public:
  Edge(int source, int destination);
  ~Edge();
 public:
  int GetSource() const;
  int GetDestination() const;
 public:
  bool SameEdge(Edge edge) const;
 private:
  int source;
  int destination;
};

#endif
