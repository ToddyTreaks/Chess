#ifndef BOARDSQUARE_H
#define BOARDSQUARE_H

#include <QGraphicsRectItem>
#include <QtCore>
#include <QtGui>


class BoardSquare : QGraphicsRectItem
{
public:
    BoardSquare();
    void setCoordinates(int x, int y);

    void updateTools();

private:
    int x;
    int y;
    bool isLightSquare;

};

#endif // BOARDSQUARE_H
