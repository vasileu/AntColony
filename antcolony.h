#ifndef ANTCOLONY_H
#define ANTCOLONY_H

#include "graph.h"
#include <QVector>
#include "ant.h"
#include "graphpainter.h"
#include <QWidget>

class AntColony
{
public:
    AntColony(int alpha, int beta, double rho, Graph &graph);
    ~AntColony();

    QVector<int> shortestRoute(int epochsCount, GraphPainter* painter, QWidget *widget);
    int routeLength();

private:
    double INIT_PHEROMONE_LEVEL;
    const double QVAL = 100;

    /*const */Graph& _graph;
    int _alpha, _beta;
    double _rho;
    QVector< QVector<double> > _pheromone;
    QVector< Ant* > _ants;

    int _shortestTourLength;
    int _bestAntNumber;
    QVector<int> _route;
    GraphPainter* _painter;
    QWidget *_widget;

    void simulateAnts();
    void updateTrails();
    void restartAnts();
    void findCurrentShortestRoute();
    int getNextVertex(int ant);
    double moveAspiration(int from, int to);
    void animate();

};

#endif // ANTCOLONY_H
