#ifndef BOARD_H
#define BOARD_H

#include <QList>

#include "piece.h"

class Board
{
public:
    Board();

private:
    QList<Piece> pieces;
    QList<Piece> takenPieces;
};

#endif // BOARD_H
