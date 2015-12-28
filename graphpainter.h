#ifndef GRAPHPAINTER_H
#define GRAPHPAINTER_H

#include "graph.h"
#include "qpainter.h"
#include "qvector.h"
#

class GraphPainter
{
    Graph* _graph;
    QPaintDevice* _paintDevice;
    QPainter _painter;
    QVector<QPoint> _vertexCoords;
    int _radiusOfVertex;
    int _radius;
private:
    void formVertexCoords();
    void drawArrow(QPoint from, QPoint to);
    void drawLine(QPoint from, QPoint to);
    void drawVertexNumber(int vertexNumber);
    void drawVertex(int vertexNumber);
    void drawEdgeWeight(int from, int to);
    void drawEdge(int from, int to, const QColor& color = Qt::red);
public:
    GraphPainter(QPaintDevice *paintDevice);
    void drawGraph(Graph *graph);
    void redrawEdge(int source, int destination, const QColor& color);
    void redrawVertex(int vertexNumber, const QColor& color);

};

#endif // GRAPHPAINTER_H
