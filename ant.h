#ifndef ANT_H
#define ANT_H

#include <QSet>
#include <QVector>

class Ant
{
   QSet<int> _visited;
   int _currentVertexNumber;
   QVector<int> _currentPath;
   int _pathLength;
public:
    Ant(int vertexNumber);
    bool visitVertex(int vertexNumber, int distance);
    bool visited(int vertexNumber);
    bool setVertexNumber(int vertexNumber);
    int currentVertexNumber();
    void restart();
    QVector<int> getCurrentPath();
    int getPathLength();
};

#endif // ANT_H
