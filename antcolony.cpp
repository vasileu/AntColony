#include "antcolony.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <vector>
#include "pallette.h"
#include <unistd.h>

#define _INFINITY 700000

AntColony::AntColony(int alpha, int beta, double rho, /*const*/ Graph &graph) :
    _alpha(alpha),
    _beta(beta),
    _rho(rho),
    _graph(graph)
{
    INIT_PHEROMONE_LEVEL = 1.0 / _graph.VertexCount();

    _shortestTourLength = _INFINITY;
    _bestAntNumber = 0;

    _pheromone.resize( _graph.VertexCount() );
    for ( int i = 0; i < _graph.VertexCount(); i++ )
    {
        _pheromone[i].resize( _graph.VertexCount() );
        _pheromone[i].fill( -1.0 );
    }

    _ants.resize( _graph.VertexCount() );
    for ( int i = 0; i < _graph.VertexCount(); i++){
        _ants[i] = new Ant(i);
    }

    VertexIterator vertIter(_graph);
    for (Vertex vertex = vertIter.begin(); !vertIter.end(); vertex = vertIter.next()){
        OutgoingEdgesIterator edgeIter(_graph, vertex);
        for (Edge edge = edgeIter.begin(); !edgeIter.end(); edge = edgeIter.nextItem()){
            _pheromone[edge.Source()][edge.Destination()] = INIT_PHEROMONE_LEVEL;
        }
    }
}

AntColony::~AntColony(){
    //need to delete _ants
}

int AntColony::routeLength()
{
    return _shortestTourLength;
}

QVector<int> AntColony::shortestRoute(int epochsCount, GraphPainter* painter, QWidget *widget)
{
    _painter = painter;
    _widget = widget;
    for (int epoch = 1; epoch <= epochsCount; epoch++){
        restartAnts();
        simulateAnts();
        updateTrails();
        findCurrentShortestRoute();
        animate();
    }
    return _route;
}

void AntColony::restartAnts()
{
    for ( int i = 0; i < _ants.count(); i++ ){
        _ants[i]->restart();
    }
}

void AntColony::findCurrentShortestRoute()
{
    for ( int i = 0; i < _ants.count(); i++ ){
        if (_ants[i]->getPathLength() < _shortestTourLength){
            _bestAntNumber = i;
            _shortestTourLength = _ants[i]->getPathLength();
            _route = _ants[i]->getCurrentPath();
        }
    }
}

void AntColony::updateTrails()
{
    //evaporation
    for ( int from = 0; from < _graph.VertexCount(); from++){
        for ( int to = 0; to < _graph.VertexCount(); to++){
            _pheromone[from][to] *= (1.0 - _rho);
        }
    }
    //add pheromone
    for ( int ant = 0; ant < _ants.count(); ant++){
        QVector<int> currentPath = _ants[ant]->getCurrentPath();//!!copying
        int vertexCount = currentPath.count();
        for ( int i = 0; i < vertexCount - 1; i++){
            int from = currentPath[i];
            int to = currentPath[i + 1];
            _pheromone[from][to] += QVAL / _ants[ant]->getPathLength();
            if (!_graph.IsDirected()){
                _pheromone[to][from] = _pheromone[from][to];
            }
        }
    }
}


void AntColony::simulateAnts()
{
    for (int ant = 0; ant < _ants.count(); ant++){
        for (int i = 0; i < _graph.VertexCount()-1; i++){
            int nextVertex = getNextVertex(ant);
            int currentVertex = _ants[ant]->currentVertexNumber();
            int distance = _graph.EdgeWeight(currentVertex, nextVertex);
            _ants[ant]->visitVertex(nextVertex, distance);
        }
        int nextVertex = _ants[ant]->getCurrentPath()[0]; //!!copying
        int currentVertex = _ants[ant]->currentVertexNumber();
        int distance = _graph.EdgeWeight(currentVertex, nextVertex);
        _ants[ant]->visitVertex(nextVertex, distance);
    }

}

int AntColony::getNextVertex(int ant)
{
    int from = _ants[ant]->currentVertexNumber();
    OutgoingEdgesIterator edgeIter(_graph, from);
    double denom = 0.0;

    for (Edge edge = edgeIter.begin(); !edgeIter.end(); edge = edgeIter.nextItem()){
        if ( !_ants[ant]->visited(edge.Destination()) ){
            denom += moveAspiration(from, edge.Destination());
        }
    }

    int to = 0;
    for (Edge edge = edgeIter.begin(); !edgeIter.end(); edge = edgeIter.nextItem()){
        if ( !_ants[ant]->visited( edge.Destination()) ){
            to = edge.Destination();
            double probability = moveAspiration(from, to) / denom;
            if ( rand() < probability*RAND_MAX ){
               break;
            }
        }
    }
    return to;
}

double AntColony::moveAspiration(int from, int to)
{
    return pow(_pheromone[from][to], _alpha) / pow(_graph.EdgeWeight(from, to), _beta);
}


void AntColony::animate()
{
    double max = 0.0;
    for( int i = 0; i < _graph.VertexCount(); i++){
        for(int j = i+1; j < _graph.VertexCount(); j++){
            if (_pheromone[i][j] > 0){
                if (_pheromone[i][j] > max){
                    max = _pheromone[i][j];
                }
            }
        }
    }
    Pallette pallette(10);
    int maxI = ceil(max);
    double step = maxI / 10.0 ;
    for( int i = 0; i < _graph.VertexCount(); i++){
        for(int j = i+1; j < _graph.VertexCount(); j++){
            if (_pheromone[i][j] > 0){
                for (int number = 0; number < 10; number++){
                    if (step*number > _pheromone[i][j]){
                        _painter->redrawEdge(i, j, pallette.getColor(10 - number));
                        break;
                    }
                }
            }
        }
    }
    _widget->repaint();
    sleep(1);
}
