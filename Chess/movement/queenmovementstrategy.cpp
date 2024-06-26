#include "queenmovementstrategy.h"

#include "bishopmovementstrategy.h"
#include "rookmovementstrategy.h"

QueenMovementStrategy::QueenMovementStrategy() {}

bool QueenMovementStrategy::canGoTo(const Position &position, const Position &targetPosition, const QMap<Position, Piece> &pieces)
{
    BishopMovementStrategy bishopMovementStrategy;
    RookMovementStrategy rookMovementStrategy;

    return bishopMovementStrategy.canGoTo(position, targetPosition, pieces) || rookMovementStrategy.canGoTo(position, targetPosition, pieces);
}
