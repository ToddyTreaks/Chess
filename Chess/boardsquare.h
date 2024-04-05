#ifndef BOARDSQUARE_H
#define BOARDSQUARE_H

#include <QGraphicsRectItem>
#include <QtCore>
#include <QtGui>


class BoardSquare : QGraphicsRectItem
{
public:

    /*
    * Constructors
    */
    BoardSquare();

    /*
    * @set the coordinates of the square
    */
    void setCoordinates(int x, int y);

    /*
    * @note update the color of tools to match the square color
    */
    void updateTools();

private:
    int x;
    int y;
    bool isLightSquare;

};

#endif // BOARDSQUARE_H
