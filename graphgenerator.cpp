#include "graphgenerator.h"
#include <stdlib.h>
#include <time.h>

GraphGenerator::GraphGenerator(int vertexCount, int density, bool directed, bool weighted, int minWeight, int maxWeight, bool oneDirect) :
    vertexCount(vertexCount),
    density(density),
    directed(directed),
    weighted(weighted),
    minWeight(minWeight),
    maxWeight(maxWeight),
    oneDirect(oneDirect)
{
}

Graph * GraphGenerator::generateGraph()
{
    Graph * G  = new Graph(vertexCount, directed);
    srand(time(NULL));
    double possibility = density / 100.0;
    for (int i = 0; i < vertexCount; i++){
        int j = ( directed && !oneDirect) ? 0 : i+1;
        for ( ; j < vertexCount; j++){
            if( i!=j ){
                if ( rand() < possibility*RAND_MAX ) {
                    Weight weight = 1;
                    if ( weighted ){
                        weight = minWeight + rand() % (maxWeight - minWeight + 1);
                    }
                    if (oneDirect){
                        if (rand() < RAND_MAX/2){
                            G->InsertEdge(Edge(i,j, weight));
                        }
                        else{
                            G->InsertEdge(Edge(j,i, weight));
                        }
                    }else{
                        G->InsertEdge(Edge(i,j, weight));
                    }
                }
            }
        }
    }
    return G;
}

int GraphGenerator::maxEdgeCount(int vertexCount, bool directed)
{
    int maxEdgeCount = vertexCount*(vertexCount-1);
    return directed ? maxEdgeCount : (maxEdgeCount >> 1);
}
