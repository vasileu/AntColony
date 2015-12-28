#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include "graph.h"
#include "graphpainter.h"
#include <QWidget>
#include "chromosome.h"
#include <QPair>

class GeneticAlgorithm
{
public:
    GeneticAlgorithm(Graph &graph, GraphPainter* painter, QWidget *widget);
    ~GeneticAlgorithm();
    
    QVector<int> shortestRoute();
    int routeLength();
       
private:
    /*const */Graph& _graph;
    GraphPainter* _painter;
    QWidget *_widget;

    QVector<Chromosome*> _population;

    QVector<int> _currShortestRoute;
    int _shortestTourLength;
    int _chromosomeSize;

    int _solved;
    
    void initPopulation(int count);
    void selectChromosomes();
    void doCrossovers();
    void mutate(int percent);
    void updatePopulation();
    bool solved();
    int pathLength(int chromosomeIndex);
    void animate();
    
};

#endif // GENETICALGORITHM_H
