#include "move.h"

Move::Move() {}

Move::Move(Piece* piece, Position nextPosition)
    : piece(piece), previousPosition(), nextPosition(nextPosition)
{
    if (piece != NULL)
    {
        previousPosition = piece->position;
    }
}

Move::Move(Piece* piece, Position previousPosition, Position nextPosition)
    : piece(piece), previousPosition(previousPosition), nextPosition(nextPosition)
{}

QString Move::toString()
{
    QString moveToString;
    if (piece == NULL)
    {
        //TODO error
        moveToString = "piece : NULL, position : %1, targetPosition : %2";
        moveToString = moveToString.arg(previousPosition.toString());
        moveToString = moveToString.arg(nextPosition.toString());
        return moveToString;
    }
    moveToString = "piece : %1, position : %2, targetPosition : %3";
    moveToString = moveToString.arg(piece->toString());
    moveToString = moveToString.arg(previousPosition.toString());
    moveToString = moveToString.arg(nextPosition.toString());
    return moveToString;
}
