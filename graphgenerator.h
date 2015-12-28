#ifndef GRAPHGENERATOR_H
#define GRAPHGENERATOR_H

#include "graph.h"

class GraphGenerator
{
    int vertexCount;
    int density;
    bool directed;
    bool weighted;
    bool oneDirect;
    int minWeight;
    int maxWeight;
    int maxEdgeCount(int vertexCount, bool directed);
public:
    GraphGenerator(int vertexCount, int density, bool directed = false, bool weighted=false, int minWeight = 0, int maxWeight = 1, bool oneDirect = true);
    Graph * generateGraph();
};

#endif // GRAPHGENERATOR_H
