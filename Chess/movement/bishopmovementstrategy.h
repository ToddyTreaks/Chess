#ifndef BISHOPMOVEMENTSTRATEGY_H
#define BISHOPMOVEMENTSTRATEGY_H

#include "movementstrategy.h"

class BishopMovementStrategy : public MovementStrategy
{
public:
    BishopMovementStrategy();

    bool canGoTo(const Position &position, const Position &targetPosition, const QMap<Position, Piece> &pieces);

private:
    bool noBlockingPieceOnPath(const Position &position, const Position &targetPosition, const QMap<Position, Piece> &pieces);
};

#endif // BISHOPMOVEMENTSTRATEGY_H
