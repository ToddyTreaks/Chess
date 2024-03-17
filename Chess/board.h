#ifndef BOARD_H
#define BOARD_H

#include <QList>

#include "move.h"
#include "piece.h"

class Board
{
public:
    Board();

    void update(Move move);
    void updateBackwards(Move move);

private:
    QList<Piece> pieces;
    QList<Piece> takenPieces;
};

#endif // BOARD_H
