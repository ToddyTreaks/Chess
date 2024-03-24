#include "bishop.h"

Bishop::Bishop() {}

Bishop::Bishop(QString color, Position position)
    : Piece(color, "B", position)
{}

bool Bishop::canGoTo(Position targetPosition, const QMap<Position, Piece> &pieces) {

    int x_target = std::abs(targetPosition.column - position.column);
    int y_target = std::abs(targetPosition.row - position.row);

    if (x_target == y_target && x_target != 0)
        return true;

    return false;
}
