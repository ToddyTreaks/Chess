#ifndef KNIGHTMOVEMENTSTRATEGY_H
#define KNIGHTMOVEMENTSTRATEGY_H

#include "movementstrategy.h"

class KnightMovementStrategy : public MovementStrategy
{
public:
    KnightMovementStrategy();

    bool canGoTo(const Position &position, const Position &targetPosition, const QMap<Position, Piece> &pieces);
};

#endif // KNIGHTMOVEMENTSTRATEGY_H
