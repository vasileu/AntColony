#include "chromosome.h"
#include <stdlib.h>
#include <time.h>
#include <QSet>

Chromosome::Chromosome(int genCount)
{
    _chromosome.resize(genCount);
    for (int i = 0; i < genCount; i++){
        _chromosome[i] = i + 1;
    }
    srand(time(NULL));
    for (int i = 0; i < genCount; i++){
        int index = i + rand() % (genCount - i + 1);
        swapGens(i, index);
    }
}

void Chromosome::swapGens(int index1, int index2)
{
    if (index1 < 0 || index1 >= _chromosome.size()){
        return;
    }
    if (index2 < 0 || index2 >= _chromosome.size()){
        return;
    }

    int tmpGen = _chromosome[index1];
    _chromosome[index1] = _chromosome[index2];
    _chromosome[index2] = tmpGen;
}

void Chromosome::moveGens(int from, int to)
{
    if (from < 0 || from >= _chromosome.size()){
        return;
    }
    if (to < 0 || to >= _chromosome.size()){
        return;
    }

    int tmpGen = _chromosome[from];
    if (from < to ){
        for (int i = from; i < to; i++){
            _chromosome[i] = _chromosome[i+1];
        }
    }
    else {
        for (int i = from; i > to; i--){
            _chromosome[i] = _chromosome[i-1];
        }
    }
    _chromosome[to] = tmpGen;
}

void Chromosome::reverseGens(int from, int to)
{
    if (from < 0 || from >= _chromosome.size()){
        return;
    }
    if (to < 0 || to >= _chromosome.size()){
        return;
    }

    if (to < from){
        int tmp = to;
        to = from;
        from = tmp;
    }


    while( from < to ){
        swapGens(from, to);
        from++;
        to--;
    }
}

int Chromosome::gen(int index)
{
    if (index < 0 || index >= _chromosome.size()){
        return -1; //out of range
    }
    return _chromosome[index];
}

void Chromosome::setGen(int index, int value)
{
    _chromosome[index] = value;
}

QVector<int> Chromosome::chromosome()
{
    return _chromosome;
}

int Chromosome::genCount()
{
    return _chromosome.size();
}

void Chromosome::crossover( Chromosome *secondParent, Chromosome *firstChild, Chromosome *secondChild)
{
    //определение точек разрыва
    int cutPoint1 = rand() % genCount();
    int cutPoint2;
    do{
        cutPoint2 = rand() % genCount();
    } while (cutPoint1 == cutPoint2);

    if (cutPoint1 > cutPoint2){
        int tmp = cutPoint1;
        cutPoint1 = cutPoint2;
        cutPoint2 = tmp;
    }

    //рекомбинация
    for (int i = 0; i < cutPoint1; i++){
        firstChild->setGen(i, _chromosome[i]);
        secondChild->setGen(i, secondParent->gen(i));
    }
    for (int i = cutPoint1; i < cutPoint2; i++){
        firstChild->setGen(i, secondParent->gen(i));
        secondChild->setGen(i, _chromosome[i]);
    }
    for (int i = cutPoint2; i < genCount(); i++){
        firstChild->setGen(i, _chromosome[i]);
        secondChild->setGen(i, secondParent->gen(i));
    }

    //нормализация
    QSet<int> fCh;
    QSet<int> sCh;
    int j = 0;
    for (int i = 0; i < genCount(); i++){
        if ( fCh.contains(firstChild->gen(i)) ){
            while ( !sCh.contains(secondChild->gen(j)) && j < genCount() ){
                sCh.insert(secondChild->gen(j));
                j++;
            }
            if (j < genCount()){
                int tmp = firstChild->gen(i);
                firstChild->setGen(i, secondChild->gen(j));
                secondChild->setGen(j, tmp);
            }
        } else {
            fCh.insert(firstChild->gen(i));
        }
    }

}
