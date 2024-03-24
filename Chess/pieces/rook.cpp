#include "rook.h"

Rook::Rook() {}

Rook::Rook(QString color, Position position)
    : Piece(color, "R", position)
{}

bool Rook::canGoTo(Position targetPosition, const QMap<Position, Piece> &pieces) {
    return true;
}
