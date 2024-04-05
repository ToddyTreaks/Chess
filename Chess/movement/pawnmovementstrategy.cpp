#include "pawnmovementstrategy.h"

PawnMovementStrategy::PawnMovementStrategy() {}

bool PawnMovementStrategy::canGoTo(const Position &position, const Position &targetPosition, const QList<Piece> &pieces)
{
    int x_target = std::abs(targetPosition.column - position.column);
    int y_target = targetPosition.row - position.row;

    Piece piece = Piece::findPiece(position, pieces);
    if (!piece.isWhite())
    {
        y_target = -y_target;
    }

    if (x_target > 1)
    {
        return false;
    }

    // capture case
    if (x_target == 1)
    {
        return (y_target == 1) && !targetPosition.isEmpty(!piece.isWhite(), pieces);
    }

    if (y_target < 0 || y_target > 2)
    {
        return false;
    }

    // starting position case
    if (y_target == 2)
    {
        return (position.row == 2 || position.row == 7);
    }

    // no capture case
    if (x_target == 0)
    {
        return true;
    }

    return false;
}
