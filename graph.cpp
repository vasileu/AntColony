#include "graph.h"

Graph::Graph( int vertexCount, bool isDirectedGraph ) :
    vertexCount( vertexCount ),
    edgeCount( 0 ),
    isDirectedGraph( isDirectedGraph )
{
    edges.resize( vertexCount );
    for ( int i = 0; i < vertexCount; i++ )
    {
        edges[i].resize( vertexCount );
        edges[i].fill( -1 );
    }
}

int Graph::EdgeCount() const
{
    return edgeCount;
}

int Graph::VertexCount() const
{
    return vertexCount;
}

bool Graph::IsDirected() const
{
    return isDirectedGraph;
}

Weight Graph::EdgeWeight( Vertex source, Vertex destination )
{
    return edges[source][destination];
}

void Graph::InsertEdge( Edge edge )
{
    Vertex i = edge.Source();
    Vertex j = edge.Destination();
    if ( edges[i][j] < 0 ){
        edgeCount++;
    }
    edges[i][j] = edge.EdgeWeight();
    if ( !isDirectedGraph ){
        edges[j][i] = edge.EdgeWeight();
    }
}

void Graph::RemoveEdge( Edge edge )
{
    Vertex i = edge.Source();
    Vertex j = edge.Destination();
    if ( edges[i][j] != -1 ){
        edgeCount--;
    }
    edges[i][j] = -1;
    if ( !isDirectedGraph ){
        edges[j][i] = -1;
    }
}

//Реализация вспомогательного класса Edge

Edge::Edge(Vertex source, Vertex destination, Weight edgeWeight) :
    source(source),
    destination(destination),
    weight(edgeWeight)
{}

Vertex Edge::Destination(){
    return destination;
}

Vertex Edge::Source(){
    return source;
}

Weight Edge::EdgeWeight(){
    return weight;
}

bool Edge::operator <(const Edge &arg){
    return (weight < arg.weight);
}

bool Edge::operator >(const Edge &arg){
    return (weight > arg.weight);
}

bool Edge::operator ==(const Edge &arg){
    return (weight == arg.weight);
}

//Реализация класса итератора по исходящим из вершины ребрам

OutgoingEdgesIterator::OutgoingEdgesIterator(const Graph &G, Vertex vertex) :
    G( G ),
    vertex( vertex ),
    i( -1 )
{

}

Edge OutgoingEdgesIterator::begin()
{
    i = -1;
    return nextItem();
}

Edge OutgoingEdgesIterator::nextItem()
{
    for( i++; i < G.vertexCount; i++){
        if ( G.edges[vertex][i] >= 0){
            return Edge(vertex,i,G.edges[vertex][i]);
        }
    }
    // возвращается некорректное ребро, но при этом функция end() == true
    return Edge();
}

bool OutgoingEdgesIterator::end()
{
    return i >= G.vertexCount;
}

//Реализация итератора по входящим ребрам

IngoingEdgesIterator::IngoingEdgesIterator(const Graph &G, Vertex vertex) :
    G(G),
    vertex(vertex),
    i(-1)
{

}
Edge IngoingEdgesIterator::begin()
{
    i = -1;
    return nextItem();
}

Edge IngoingEdgesIterator::nextItem()
{
    for( i++; i < G.vertexCount; i++){
        if ( G.edges[i][vertex] >= 0 ){
            return Edge(i, vertex, G.edges[i][vertex]);
        }
    }
    // возвращается некорректное ребро, но при этом функция end() == true
    return Edge();
}

bool IngoingEdgesIterator::end()
{
    return i >= G.VertexCount();
}

//Реализация итератора по вершинам графа

VertexIterator::VertexIterator(const Graph &G) :
    G(G)
{}

Vertex VertexIterator::begin(){
    currentVertex = -1;
    return next();
}

Vertex VertexIterator::next(){
    currentVertex++;
    return currentVertex;
}

bool VertexIterator::end(){
    return currentVertex >= G.VertexCount();
}


//Реализация итератора по ребрам графа
EdgesIterator::EdgesIterator(const Graph &G) :
    G(G)
{}

Edge EdgesIterator::begin(){
    i = 0;
    j = 0;
    currentEdgeNumber = 0;
    isEnd = false;
    return nextItem();
}

Edge EdgesIterator::nextItem(){
    for ( int row = i; row < G.VertexCount(); row++){
        j++;
        if ( j >= G.VertexCount() ){
            j = G.IsDirected() ? -1 : row;
            continue;
        }

        for ( int coloumn = j; coloumn < G.VertexCount(); coloumn++){
            if(G.edges[row][coloumn] >= 0){
                i = row;
                j = coloumn;
                currentEdgeNumber++;
                return Edge(row, coloumn, G.edges[row][coloumn]);
            }
        }

    }
    isEnd = true;
    return Edge();
}

bool EdgesIterator::end(){
    return isEnd;
}
