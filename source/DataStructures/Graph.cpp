#include <DataStructures/Graph.h>

Graph::Graph() {
}

Graph::~Graph() {
}

bool Graph::AddVertex(int v) {
    vertices.push_back(v);
}

bool Graph::RemoveVertex(int v) {
    bool check = false;
    for (int i = 0 ; i < vertices.size() ; ++i) {
        if (vertices[i] == v) {
            vertices.erase(vertices.begin()+i);
            check = true;
        }
    }
    return check;
}

bool Graph::AddEdge(int v1, int v2) { // 会有添加不成功的例子吗？
    if (ContainsVertex(v1) && ContainsVertex(v2)) {
        Edge new_edge(v1, v2);
        edges.push_back(new_edge);
        return true;
    }
    else
        return false;
}

bool Graph::RemoveEdge(int v1, int v2) {
    bool check = false;

    Edge temp(v1, v2);
    for (int i = 0 ; i < edges.size() ; ++i) {
        if (edges[i].SameEdge(temp)) {
            edges.erase(edges.begin()+i);
            check = true;
            break;
        }
    }
    return check;
}

int Graph::CountVertices() const {
    return vertices.size();
}

int Graph::CountEdges() const {
    return edges.size();
}

bool Graph::ContainsVertex(int v) const {
    bool check = false;
    for (int i = 0 ; i < vertices.size() ; ++i) {
        if (vertices[i] == v) {
            check = true;
            break;
        }
    }
    return check;
}

bool Graph::ContainsEdge(int v1, int v2) const {
    bool check = false;
    Edge temp(v1, v2);
    for (int i = 0 ; i < edges.size() ; ++i) {
        if (edges[i].SameEdge(temp)) {
            check = true;
            break;
        }
    }
    return check;
}

std::vector<int> Graph::GetVertices() const {
    static std::vector<int> temp = vertices;
    return temp;
}

std::vector<Edge> Graph::GetEdges() const {
    static std::vector<Edge> temp = edges;
    return temp;
}

std::vector<Edge> Graph::GetIncomingEdges(int v) const {
    static std::vector<Edge> temp;
    for (int i = 0 ; i < edges.size() ; ++i) {
        if (edges[i].GetDestination() == v) {
            temp.push_back(edges[i]);
        }
    }
    return temp;
}

std::vector<Edge> Graph::GetOutgoingEdges(int v) const {
    static std::vector<Edge> temp;
    for (int i = 0 ; i < edges.size() ; ++i) {
        if (edges[i].GetSource() == v) {
            temp.push_back(edges[i]);
        }
    }
    return temp;
}

int Graph::GetDegree(int v) const {
    int ans = 0;
    for (int i = 0 ; i < edges.size() ; ++i) {
        if (edges[i].GetSource() == v) {
            ans++;
        }
    }
    return ans;
}

std::vector<int> Graph::GetNeighbors(int v) const {
    static std::vector<int> temp;
    for (int i = 0 ; i < edges.size() ; ++i) {
        if (edges[i].GetSource() == v) {
            temp.push_back(edges[i].GetSource());
        }
        if (edges[i].GetDestination() == v) {
            temp.push_back(edges[i].GetDestination());
        }
    }
    return temp;
}
