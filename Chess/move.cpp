#include "move.h"

Move::Move() {}

Move::Move(Piece piece, Position nextPosition)
    : piece(piece), nextPosition(nextPosition)
{}

QString Move::toString()
{
    return QString("piece : %1, targetPosition : %2").arg(piece.toString()).arg(nextPosition.toString());
}

