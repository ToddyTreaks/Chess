#ifndef BOARDDRAWER_H
#define BOARDDRAWER_H

#include "piece.h"
#include "position.h"

#include <QGraphicsScene>
#include <QLabel>

class BoardDrawer
{
public:
    BoardDrawer();

    void drawSquares(QGraphicsScene* scene);
    void drawPieces(QGraphicsScene* scene, const QList<Piece> &pieces);

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
