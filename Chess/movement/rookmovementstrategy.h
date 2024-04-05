#ifndef ROOKMOVEMENTSTRATEGY_H
#define ROOKMOVEMENTSTRATEGY_H

#include "movementstrategy.h"

class RookMovementStrategy : public MovementStrategy
{
public:
    RookMovementStrategy();

    bool canGoTo(const Position &position, const Position &targetPosition, const QList<Piece> &pieces);

private:
    bool noBlockingPieceOnColumn(const Position &position, const Position &targetPosition, const QList<Piece> &pieces);
    bool noBlockingPieceOnRow(const Position &position, const Position &targetPosition, const QList<Piece> &pieces);

};

#endif // ROOKMOVEMENTSTRATEGY_H
