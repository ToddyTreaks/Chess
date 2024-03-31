#include "move.h"

#include <QDebug>

Move::Move() {}

Move::Move(Piece piece, Position nextPosition)
    : Move(piece, piece.position, nextPosition)
{}

Move::Move(Piece piece, Position previousPosition, Position nextPosition)
    : piece(piece), previousPosition(previousPosition), nextPosition(nextPosition)
{
    capture = false;
    castlingKingside = false;
    castlingQueenside = false;
}

QString Move::toString()
{
    QString moveToString;
    moveToString = "piece : %1, position : %2, targetPosition : %3";
    moveToString = moveToString.arg(piece.toString());
    moveToString = moveToString.arg(previousPosition.toString());
    moveToString = moveToString.arg(nextPosition.toString());
    return moveToString;
}

Piece Move::getPiece()
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

Piece Move::getCapturedPiece()
{
    return capturedPiece;
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

void Move::setCapturedPiece(Piece piece)
{
    capturedPiece = Piece(piece);
    capture = true;
}

void Move::setKingsideCastlingKing(Piece castlingKing)
{
    piece = castlingKing;
    castlingKingside = true;
}

void Move::setQueensideCastlingKing(Piece castlingKing)
{
    piece = castlingKing;
    castlingQueenside = true;
}

void Move::castleKingside(QMap<Position, Piece> &pieces)
{
    if (!canCastleKingside(pieces))
    {
        // TODO error
        return;
    }

    Piece rook;
    Position rookPosition(1, 8);

    if (piece.getColor() == "Black")
    {
        rookPosition.row = 8;
    }
    rook = pieces.value(rookPosition);

    Position kingNextPosition(piece.position.row, piece.position.column + 2);
    Position rookNextPosition(rookPosition.row, rookPosition.column - 2);

    pieces.remove(piece.position);
    pieces.remove(rookPosition);

    piece.position = kingNextPosition;
    rook.position = rookNextPosition;
    pieces.insert(kingNextPosition, piece);
    pieces.insert(rookNextPosition, rook);

}

void Move::undoCastleKingside(QMap<Position, Piece> &pieces)
{
    Piece rook;
    Position rookPosition(1, 6);

    if (piece.getColor() == "Black")
    {
        rookPosition.row = 8;
    }
    rook = pieces.value(rookPosition);

    Position kingPreviousPosition(piece.position.row, piece.position.column - 2);
    Position rookPreviousPosition(rookPosition.row, rookPosition.column + 2);

    pieces.remove(piece.position);
    pieces.remove(rookPosition);

    piece.position = kingPreviousPosition;
    rook.position = rookPreviousPosition;
    pieces.insert(kingPreviousPosition, piece);
    pieces.insert(rookPreviousPosition, rook);

}

bool Move::canCastleKingside(const QMap<Position, Piece> &pieces)
{
    // TODO
    return true;
}

bool Move::canCastleQueenside(const QMap<Position, Piece> &pieces)
{
    // TODO
    return true;
}
