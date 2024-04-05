#ifndef KINGMOVEMENTSTRATEGY_H
#define KINGMOVEMENTSTRATEGY_H

#include "movementstrategy.h"

class KingMovementStrategy : public MovementStrategy
{
public:
    KingMovementStrategy();

    bool canGoTo(const Position &position, const Position &targetPosition, const QList<Piece> &pieces);
};

#endif // KINGMOVEMENTSTRATEGY_H
