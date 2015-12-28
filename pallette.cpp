#include "pallette.h"

Pallette::Pallette(int count)
{
    int R = 0;
    int G = 0;
    int B = 0;

    int colorStep = 2 * 255 / count;

    while ( R < 255 ){
        QColor tint( R, G, B );
        _pallette.push_back(tint);
        R += colorStep;
        if (R > 255){
            G = R - 255;
            B = G;
            R = 255;
        }
    }

    while ( G < 255 ){
        QColor tint(R, G, B);
        _pallette.push_back(tint);
        G += colorStep;
        if (G > 255){
            R = 255;
        }
        B = G;
    }
}


QColor Pallette::getColor(int number)
{
    if (number < 0){
        return _pallette[0];
    }
    if ( number > _pallette.size() - 1 ){
        return _pallette[_pallette.size() - 1];
    }
    return _pallette[number];
}
