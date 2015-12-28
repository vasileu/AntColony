#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include <QVector>

class Chromosome
{
   QVector<int> _chromosome;
public:
    Chromosome(int genCount);
    void swapGens(int index1, int index2);
    void moveGens(int from, int to);
    void reverseGens(int from, int to);
    int gen(int index);
    void setGen(int index, int value);
    int genCount();
    void crossover(Chromosome *secondParent, Chromosome* firstChild, Chromosome* secondChild);
    QVector<int> chromosome();
};

#endif // CHROMOSOME_H
