#include "move.h"

Move::Move() {}

Move::Move(Piece* piece, Position nextPosition)
    : Move(piece, piece->position, nextPosition)
{}

Move::Move(Piece* piece, Position previousPosition, Position nextPosition)
    : piece(piece), previousPosition(previousPosition), nextPosition(nextPosition)
{
    capture = false;
    castlingKingside = false;
    castlingQueenside = false;
}

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

Piece* Move::getPiece()
{
    return piece;
}

Position Move::getPreviousPosition()
{
    return previousPosition;
}

Position Move::getNextPosition()
{
    return nextPosition;
}

bool Move::isCapture()
{
    return capture;
}

bool Move::isCastlingKingside()
{
    return castlingKingside;
}

bool Move::isCastlingQueenside()
{
    return castlingQueenside;
}

void Move::setCapturedPiece(Piece* capturedPiece)
{
    capturedPiece = capturedPiece;
    capture = true;
}

void Move::setKingsideCastlingKing(Piece* castlingKing)
{
    piece = castlingKing;
    castlingKingside = true;
}

void Move::setQueensideCastlingKing(Piece* castlingKing)
{
    piece = castlingKing;
    castlingQueenside = true;
}
