#include "queen.h"

Queen::Queen() {}

Queen::Queen(QString color, Position position)
    : Piece(color, "Q", position)
{}

bool Queen::canGoTo(Position targetPosition, const QMap<Position, Piece*> &pieces) {
    return true;
}
