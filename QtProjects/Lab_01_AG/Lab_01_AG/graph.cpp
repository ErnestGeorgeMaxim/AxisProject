#ifndef GRAPH_H
#define GRAPH_H

#include "edge.h"
#include <vector>

class Graph
{
public:
    Graph();
    void addNode(QPoint p) {
        //verificare suprapunere noduri
        Node n;
        n.setPos(p);
        n.setValue(m_nodes.size() + 1);
        m_nodes.push_back(n);

    };
    void addEdge(Node f, Node s)
    {
        //verificare multigraf

        Edge e(f, s);
        m_edges.push_back(e);

    };
    std::vector<Node>& getNodes() { return m_nodes; };
    std::vector<Edge>& getEdges() { return m_edges; };

private:
    std::vector<Node> m_nodes;
    std::vector<Edge> m_edges;
    //matrice de adiacenta
    //lista de adiacenta
    bool isOriented;

};

#endif // GRAPH_H
