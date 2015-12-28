#ifndef GRAPH_H
#define GRAPH_H

#include "QVector"

typedef int Weight;
typedef int Vertex;

class Edge
{
    Vertex source;
    Vertex destination;
    Weight weight;
public:
    Edge(Vertex source = 0, Vertex destination = 0, Weight edgeWeight = 0);

    Vertex Source();
    Vertex Destination();
    Weight EdgeWeight();

    bool operator> (const Edge &arg);
    bool operator< (const Edge &arg);
    bool operator== (const Edge &arg);
};

class Graph
{
    int vertexCount;
    int edgeCount;
    bool isDirectedGraph;
    QVector < QVector <Weight> > edges;
public:
    Graph(int vertexCount, bool isDirectedGraph = true);
    int VertexCount() const;
    int EdgeCount() const;
    bool IsDirected() const;
    void InsertEdge(Edge edge);
    void RemoveEdge(Edge edge);
    Weight EdgeWeight(Vertex source, Vertex destination);

    friend class OutgoingEdgesIterator;
    friend class IngoingEdgesIterator;
    friend class VertexIterator;
    friend class EdgesIterator;
};

class EdgesIterator
{
    const Graph & G;
    int i;
    int j;
    int currentEdgeNumber;
    bool isEnd;
public:
    EdgesIterator(const Graph& G);
    Edge begin();
    Edge nextItem();
    bool end();
};

class OutgoingEdgesIterator
{
    const Graph & G;
    Vertex vertex;
    int i;
public:
    OutgoingEdgesIterator(const Graph& G, Vertex vertex);
    Edge begin();
    Edge nextItem();
    bool end();
};

class IngoingEdgesIterator
{
    const Graph & G;
    Vertex vertex;
    int i;
public:
    IngoingEdgesIterator(const Graph& G, Vertex vertex);
    Edge begin();
    Edge nextItem();
    bool end();
};

class VertexIterator
{
    const Graph &G;
    Vertex currentVertex;
public:
    VertexIterator(const Graph& G);
    Vertex begin();
    Vertex next();
    bool end();
};

#endif // GRAPH_H
