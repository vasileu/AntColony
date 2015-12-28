#ifndef PALLETTE_H
#define PALLETTE_H

#include <QColor>
#include <QVector>

class Pallette
{
    QVector<QColor> _pallette;
public:
    Pallette(int count);
    QColor getColor(int number);
};

#endif // PALLETTE_H
