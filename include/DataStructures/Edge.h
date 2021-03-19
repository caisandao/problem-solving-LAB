#ifndef EDGE_H
#define EDGE_H

class Edge {
 public:
  Edge(int source, int destination);
  virtual ~Edge();
 public:
  int GetSource() const;
  int GetDestination() const;
 private:
  int source;
  int destination;
};

#endif
