#include "ant.h"

Ant::Ant(int vertexNumber)
{
    setVertexNumber(vertexNumber);
    _pathLength = 0;
}

bool Ant::visited(int vertexNumber)
{
    return _visited.contains(vertexNumber);
}

bool Ant::visitVertex(int vertexNumber, int distance)
{
   /* if (visited(vertexNumber)){
        return false;
    }*/
    setVertexNumber(vertexNumber);
    //_visited.insert(vertexNumber);
    _pathLength += distance;
    return true;
}

bool Ant::setVertexNumber(int vertexNumber)
{
    /*if (visited(vertexNumber)){
        return false;
    }*/
    _currentVertexNumber = vertexNumber;
    _currentPath.push_back(vertexNumber);
    _visited.insert(vertexNumber);
    return true;
}

int Ant::currentVertexNumber()
{
    return _currentVertexNumber;
}

void Ant::restart()
{
    _visited.clear();
    _currentPath.clear();
    _pathLength = 0;
    setVertexNumber(_currentVertexNumber);
}

int Ant::getPathLength()
{
    return _pathLength;
}

QVector<int> Ant::getCurrentPath()
{
    return _currentPath;
}
