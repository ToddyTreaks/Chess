#ifndef QUEEN_H
#define QUEEN_H

#include "movementstrategy.h"

class QueenMovementStrategy : public MovementStrategy
{
public:
    QueenMovementStrategy();

    bool canGoTo(const Position &position, const Position &targetPosition, const QList<Piece> &pieces);
};

#endif // QUEEN_H
