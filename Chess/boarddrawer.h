#ifndef BOARDDRAWER_H
#define BOARDDRAWER_H

#include "piece.h"
#include "position.h"

#include <QGraphicsScene>
#include <QLabel>

class BoardDrawer
{
public:

    /*
    * Constructors
    */
    BoardDrawer();

    /*
    * @param scene the scene to draw the squares on
    * @note draw the squares of the board
    */
    void drawSquares(QGraphicsScene* scene);

    /*
    * @param scene the scene to draw the pieces on
    * @param QMap<Position, Piece>: a map of the pieces on the board that use the position as key
    * @note draw the pieces on the board
    */
    void drawPieces(QGraphicsScene* scene, const QMap<Position, Piece> &pieces);

private:
    QBrush lightBrush;
    QBrush darkBrush;
    QPen lightPen;
    QPen darkPen;

    const int SQUARE_SIZE = 50;

    void drawPiece(Piece piece, QGraphicsScene* scene);
    int getxFromPosition(Position position);
    int getyFromPosition(Position position);
};

#endif // BOARDDRAWER_H
