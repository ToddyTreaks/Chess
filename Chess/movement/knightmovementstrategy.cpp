#include "knightmovementstrategy.h"

KnightMovementStrategy::KnightMovementStrategy() {}

// KnightMovementStrategy::KnightMovementStrategy(QString color, Position position)
//     : Piece(color, "N", position)
// {}

bool KnightMovementStrategy::canGoTo(const Position &position, const Position &targetPosition, const QMap<Position, Piece> &pieces) {

    int x_target = std::abs(targetPosition.column - position.column);
    int y_target = std::abs(targetPosition.row - position.row);

    if ((x_target == 1 && y_target ==2) || (x_target == 2 && y_target ==1))
        return true;

    return false;
}
