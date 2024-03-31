#include "bishopmovementstrategy.h"

BishopMovementStrategy::BishopMovementStrategy() {}

bool BishopMovementStrategy::canGoTo(const Position &position, const Position &targetPosition, const QMap<Position, Piece> &pieces)
{
    int x_target = std::abs(targetPosition.column - position.column);
    int y_target = std::abs(targetPosition.row - position.row);

    if (x_target != y_target)
    {
        return false;
    }

    if (x_target == 0)
    {
        return false;
    }

    return true;
}

bool BishopMovementStrategy::noBlockingPieceOnPath(const Position &position, const Position &targetPosition, const QMap<Position, Piece> &pieces)
{
    int moveSquareNumber = std::abs(targetPosition.column - position.column);
    int rowIncrementSign = (targetPosition.row - position.row) / moveSquareNumber;
    int columnIncrementSign = (targetPosition.column - position.column) / moveSquareNumber;

    for (int i = 1; i < moveSquareNumber; i++)
    {
        if (!Position(position.row + i*rowIncrementSign, position.column + i*columnIncrementSign).isEmpty(pieces))
        {
            return false;
        }
    }

    return true;
}
