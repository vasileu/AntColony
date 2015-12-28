#include "graphpainter.h"
#include "math.h"


#define EDGE_WIDTH 7

GraphPainter::GraphPainter(QPaintDevice* paintDevice) :
    _paintDevice(paintDevice)
{
    _radius = 370;
    _radiusOfVertex = 30;
    _graph = NULL;
}


void GraphPainter::drawGraph(Graph *graph)
{
    _painter.begin(_paintDevice);
    _painter.setPen(QPen(Qt::red));
    _painter.setBrush(QBrush(Qt::green));
    _painter.setRenderHint(QPainter::Antialiasing, true);

    _graph = graph;
    formVertexCoords();
    for ( int vertexNumber = 0; vertexNumber < _vertexCoords.size(); vertexNumber++){
        drawVertex(vertexNumber);
    }


    for ( int source = 0; source < _graph->VertexCount(); source++){
        int destination = ( _graph->IsDirected() ) ? 0 : source+1;
        for (; destination < _graph->VertexCount(); destination++){
            if ( _graph->EdgeWeight( source, destination) > 0){
               drawEdge(source, destination);
            }
        }
    }


    _painter.end();
}

void GraphPainter::redrawVertex(int vertexNumber, const QColor &color)
{
    _painter.begin(_paintDevice);

    QBrush brush = _painter.brush();
    _painter.setBrush(QBrush(color));
    drawVertex(vertexNumber);
    _painter.setBrush(brush);

    _painter.end();
}

void GraphPainter::redrawEdge(int source, int destination, const QColor &color)
{
    _painter.begin(_paintDevice);

    QPen pen = _painter.pen();
    _painter.setPen(QPen(color));
    drawEdge(source, destination, color);
    _painter.setPen(pen);

    _painter.end();
}

void GraphPainter::drawVertex(int vertexNumber)
{
    _painter.drawEllipse(_vertexCoords[vertexNumber], _radiusOfVertex, _radiusOfVertex);
    drawVertexNumber(vertexNumber);
}

void GraphPainter::drawVertexNumber(int vertexNumber)
{
    _painter.drawText(_vertexCoords[vertexNumber], QString::number(vertexNumber));
}

void GraphPainter::drawEdge(int from, int to, const QColor& color)
{
    QPen pen = _painter.pen();
    _painter.setPen(QPen(color, EDGE_WIDTH));

    if ( _graph->IsDirected()){
        drawArrow(_vertexCoords[from], _vertexCoords[to]);
    } else {
        drawLine(_vertexCoords[from], _vertexCoords[to]);
    }

    _painter.setPen(pen);
    drawEdgeWeight(from, to);
}

void GraphPainter::drawEdgeWeight(int from, int to)
{
    int weight = _graph->EdgeWeight(from, to);

    int x = fabs(_vertexCoords[from].x() - _vertexCoords[to].x()) / 2;
    int minx = (_vertexCoords[from].x() < _vertexCoords[to].x()) ? _vertexCoords[from].x() : _vertexCoords[to].x();
    x += minx;

    int y = fabs(_vertexCoords[from].y() - _vertexCoords[to].y()) / 2;
    int miny = (_vertexCoords[from].y() < _vertexCoords[to].y()) ? _vertexCoords[from].y() : _vertexCoords[to].y();
    y += miny;

    _painter.drawText(x, y-20, QString::number(weight));
}

void GraphPainter::drawArrow(QPoint from, QPoint to)
{
   // _painter.drawLine(from, to);
    double factor = _radiusOfVertex / sqrt(pow((from.x() - to.x()), 2) + pow((from.y() - to.y()),2));
    QPoint finish;
    finish.rx() = to.x() + (from.x()-to.x()) * factor;
    finish.ry() = to.y() + (from.y()-to.y()) * factor;
    _painter.drawEllipse(finish, 3, 3);

    drawLine(from, to);
}

void GraphPainter::drawLine(QPoint from, QPoint to)
{
    double factor = (_radiusOfVertex + EDGE_WIDTH / 2) / sqrt(pow((from.x() - to.x()), 2) + pow((from.y() - to.y()),2));
    QPointF start;
    start.rx() = from.x() + (to.x()-from.x()) * factor;
    start.ry() = from.y() + (to.y()-from.y()) * factor;

    QPointF finish;
    finish.rx() = to.x() + (from.x()-to.x()) * factor;
    finish.ry() = to.y() + (from.y()-to.y()) * factor;

    _painter.drawLine(start, finish);
}

void GraphPainter::formVertexCoords()
{
    _vertexCoords.clear();
    QPoint center(_paintDevice->width()/2, _paintDevice->height()/2);
    for ( int vertexNumber = 0; vertexNumber < _graph->VertexCount(); vertexNumber++){
        double angle = 2 * 3.14 * vertexNumber / _graph->VertexCount();
        int x = center.x() + cos(angle) * _radius;
        int y = center.y() + sin(angle) * _radius;
        _vertexCoords.push_back(QPoint(x,y));
    }
}

