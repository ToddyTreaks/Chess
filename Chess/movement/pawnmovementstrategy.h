#ifndef PAWNMOVEMENTSTRATEGY_H
#define PAWNMOVEMENTSTRATEGY_H

#include "movementstrategy.h"

class PawnMovementStrategy : public MovementStrategy
{
public:
    PawnMovementStrategy();

    bool canGoTo(const Position &position, const Position &targetPosition, const QMap<Position, Piece> &pieces);
};

#endif // PAWNMOVEMENTSTRATEGY_H
