#include "geneticalgorithm.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

GeneticAlgorithm::GeneticAlgorithm(Graph &graph, GraphPainter *painter, QWidget *widget) :
    _graph(graph),
    _painter(painter),
    _widget(widget)
{
    _chromosomeSize = _graph.VertexCount() - 1;
    _shortestTourLength = RAND_MAX;
    _solved = 0;
}

GeneticAlgorithm::~GeneticAlgorithm()
{
    //delete chromosomes in population
}

QVector<int> GeneticAlgorithm::shortestRoute()
{
    initPopulation(200);
    int i = 0;
    while (/* !solved() */i < 100){
        selectChromosomes();
        doCrossovers();
        mutate(30);
        updatePopulation();
        animate();
        i++;
    }
    _currShortestRoute.push_back(0);
    _currShortestRoute.push_front(0);
    return _currShortestRoute;
}

int GeneticAlgorithm::routeLength()
{
    return _shortestTourLength;
}

void GeneticAlgorithm::initPopulation(int count)
{
    for (int i = 0; i < count; i++){
        _population.push_back( new Chromosome( _chromosomeSize ) );
    }
    updatePopulation();

}

void GeneticAlgorithm::mutate(int percent)
{
    srand(time(NULL));
    for (int i = 0; i < _population.size(); i++){
        double possibility = percent / 100.0;
        if ( rand() < possibility*RAND_MAX ) {
            int mutationKind = rand() % 3;
            int index1 = rand() % _chromosomeSize;
            int index2 = rand() % _chromosomeSize;
            switch (mutationKind) {
            case 0:
                _population[i]->moveGens(index1, index2);
                break;
            case 1:
                _population[i]->reverseGens(index1, index2);
                break;
            case 2:
                _population[i]->swapGens(index1, index2);
                break;
            default:
                break;
            }
        }
    }
}

int GeneticAlgorithm::pathLength(int chromosomeIndex)
{
    Chromosome* chromosome = _population[chromosomeIndex];
    int result = _graph.EdgeWeight(0, chromosome->gen(0));
    for (int i = 0; i <_chromosomeSize - 1; i++){
        int source = chromosome->gen(i);
        int dest = chromosome->gen(i+1);
        result += _graph.EdgeWeight(source, dest);
    }
    result += _graph.EdgeWeight(chromosome->gen(_chromosomeSize - 1), 0);
    return result;
}

void GeneticAlgorithm::updatePopulation()
{
    // !!!!!!!!solved!!!!!
    bool changed = false;
    for (int i = 0; i < _population.size(); i++){
        if (pathLength(i) < _shortestTourLength){
            _currShortestRoute = _population[i]->chromosome();
            _shortestTourLength = pathLength(i);
            changed = true;
        }
    }
    if (changed){
        _solved = 0;
    } else {
        _solved++;
    }
}

bool GeneticAlgorithm::solved()
{
    return _solved > 10;
}

void GeneticAlgorithm::selectChromosomes()
{
    for (int i = 0; i < _population.size()-1; i++){
        for (int j = _population.size()-1; i < j; j--){
            if ( pathLength(j-1) > pathLength(j)){
                Chromosome *tmp  = _population[j-1];
                _population[j-1] = _population[j];
                _population[j] = tmp;
            }
        }
    }
}


void GeneticAlgorithm::doCrossovers()
{
    srand(time(NULL));
    int halfSize = _population.size()/2;

    // delete bad chromosomes
    for (int i = halfSize; i < _population.size(); i++){
        delete _population[i];
    }

    //crossing over
    for (int i = 0; i < _population.size()/4; i++){
        int partner = 0;
        do {
            partner = rand() % (halfSize);
        } while (partner == i);

        Chromosome *firstChild, *secondChild;
        firstChild = new Chromosome(_population[i]->genCount());
        secondChild = new Chromosome(_population[i]->genCount());

        _population[i]->crossover(_population[partner], firstChild, secondChild);
        _population[i*2 + halfSize] = firstChild;
        _population[i*2 + halfSize + 1] = secondChild;

    }
}

void GeneticAlgorithm::animate()
{
    _painter->drawGraph( &_graph );
    _painter->redrawEdge(0, _currShortestRoute[0], Qt::blue);
    for (int i = 0; i < _currShortestRoute.size() - 1; i++){
        _painter->redrawEdge(_currShortestRoute[i], _currShortestRoute[i+1], Qt::blue);
    }
    _painter->redrawEdge(_currShortestRoute[_currShortestRoute.size() - 1], 0, Qt::blue);
    _widget->repaint();
    usleep(500);
}
