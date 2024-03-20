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
    Piece * pieces[8][8];
};

#endif // BOARD_H
