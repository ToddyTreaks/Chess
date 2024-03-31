#include "boardsquare.h"

BoardSquare::BoardSquare() {}

void BoardSquare::setCoordinates(int x, int y)
{
    x = x;
    y = y;
    isLightSquare = false;
    if ((x+y) % 2 == 0)
    {
        isLightSquare = true;
    }
}

void BoardSquare::updateTools()
{
    if (isLightSquare)
    {
        setPen(QPen(Qt::yellow));
        setBrush(QBrush(Qt::yellow));
    }
    else
    {
        setPen(QPen(Qt::black));
        setBrush(QBrush(Qt::black));
    }
}

