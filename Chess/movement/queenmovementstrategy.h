#ifndef QUEEN_H
#define QUEEN_H

#include "movementstrategy.h"

class QueenMovementStrategy : public Piece
{
public:
    QueenMovementStrategy();

    bool canGoTo(const Position &position, const Position &targetPosition, const QMap<Position, Piece> &pieces);
};

#endif // QUEEN_H
