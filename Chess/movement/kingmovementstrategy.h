#ifndef KINGMOVEMENTSTRATEGY_H
#define KINGMOVEMENTSTRATEGY_H

#include "movementstrategy.h"

class KingMovementStrategy : public MovementStrategy
{
public:
    KingMovementStrategy();

    bool canGoTo(const Position &position, const Position &targetPosition, const QMap<Position, Piece> &pieces);
};

#endif // KINGMOVEMENTSTRATEGY_H
