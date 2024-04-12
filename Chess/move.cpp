#include "move.h"

Move::Move()
{
    initializeAttributes();
}

Move::Move(const Piece &piece, const Position &nextPosition)
    : Move(piece, piece.position, nextPosition)
{}

Move::Move(const Piece &piece, const Position &previousPosition, const Position &nextPosition)
    : piece(piece), previousPosition(previousPosition), nextPosition(nextPosition)
{
    initializeAttributes();
}

void Move::initializeAttributes()
{
    capture = false;
    promotion = false;
    castlingKingside = false;
    castlingQueenside = false;
}

QString Move::toString() const
{
    QString moveToString;
    moveToString = "piece : %1, position : %2, targetPosition : %3";
    moveToString = moveToString.arg(piece.toString());
    moveToString = moveToString.arg(previousPosition.toString());
    moveToString = moveToString.arg(nextPosition.toString());
    return moveToString;
}

Piece Move::getPiece() const
{
    return piece;
}

Position Move::getPreviousPosition() const
{
    return previousPosition;
}

Position Move::getNextPosition() const
{
    return nextPosition;
}

bool Move::isCapture() const
{
    return capture;
}

Piece Move::getCapturedPiece() const
{
    return capturedPiece;
}

bool Move::isPromotion() const
{
    return promotion;
}

Piece Move::getPiecePromotedTo() const
{
    return piecePromotedTo;
}

bool Move::isCastlingKingside() const
{
    return castlingKingside;
}

bool Move::isCastlingQueenside() const
{
    return castlingQueenside;
}

void Move::setCapturedPiece(Piece pieceCaptured)
{
    capturedPiece = Piece(pieceCaptured);
    capture = true;
}

void Move::setPiecePromotedTo(QString piecePromotedToIdentifier)
{
    piecePromotedTo = Piece(piece.isWhite(), piecePromotedToIdentifier, nextPosition);
    promotion = true;
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

void Move::applyMove(QList<Piece> &pieces) const
{
    if (castlingKingside)
    {
        castleKingside(pieces);
        return;
    }

    if (castlingQueenside)
    {
        castleQueenside(pieces);
        return;
    }

    if (capture)
    {
        pieces.removeAll(capturedPiece);
    }

    pieces.removeAll(piece);

    Piece pieceAfterMove(piece);
    pieceAfterMove.position = nextPosition;

    if (promotion)
    {
        pieceAfterMove= piecePromotedTo;
    }

    pieces.append(pieceAfterMove);
}

void Move::undoMove(QList<Piece> &pieces) const
{
    if (castlingKingside)
    {
        undoCastleKingside(pieces);
        return;
    }

    if (castlingQueenside)
    {
        undoCastleQueenside(pieces);
        return;
    }

    if (promotion)
    {
        pieces.removeAll(piecePromotedTo);
    }

    if (capture)
    {
        pieces.append(capturedPiece);
    }

    Piece pieceAfterMove(piece);
    pieceAfterMove.position = nextPosition;
    pieces.removeAll(pieceAfterMove);

    pieces.append(piece);
}

void Move::castleKingside(QList<Piece> &pieces) const
{
    if (!canCastleKingside(pieces))
    {
        // TODO error
        return;
    }

    Piece rook;
    Position rookPosition(1, 8);

    if (!piece.isWhite())
    {
        rookPosition.row = 8;
    }
    rook = Piece::findPiece(rookPosition, pieces);

    Position kingNextPosition(piece.position.row, piece.position.column + 2);
    Position rookNextPosition(rookPosition.row, rookPosition.column - 2);

    pieces.removeAll(piece);
    pieces.removeAll(rook);

    Piece pieceAfterMove(piece);
    pieceAfterMove.position = kingNextPosition;
    pieces.append(pieceAfterMove);

    rook.position = rookNextPosition;
    pieces.append(rook);

}

void Move::castleQueenside(QList<Piece> &pieces) const
{
    if (!canCastleQueenside(pieces))
    {
        // TODO error
        return;
    }

    Piece rook;
    Position rookPosition(1, 1);

    if (!piece.isWhite())
    {
        rookPosition.row = 8;
    }
    rook = Piece::findPiece(rookPosition, pieces);

    Position kingNextPosition(piece.position.row, piece.position.column - 2);
    Position rookNextPosition(rookPosition.row, rookPosition.column + 3);

    pieces.removeAll(piece);
    pieces.removeAll(rook);

    Piece pieceAfterMove(piece);
    pieceAfterMove.position = kingNextPosition;
    pieces.append(pieceAfterMove);

    rook.position = rookNextPosition;
    pieces.append(rook);

}

void Move::undoCastleKingside(QList<Piece> &pieces) const
{
    Piece rook;
    Position rookPosition(1, 6);

    if (!piece.isWhite())
    {
        rookPosition.row = 8;
    }
    rook = Piece::findPiece(rookPosition, pieces);

    Position kingNextPosition(piece.position.row, piece.position.column + 2);
    Position rookPreviousPosition(rookPosition.row, rookPosition.column + 2);

    Piece pieceAfterMove(piece);
    pieceAfterMove.position = kingNextPosition;
    pieces.removeAll(pieceAfterMove);
    pieces.removeAll(rook);


    pieces.append(piece);
    rook.position = rookPreviousPosition;
    pieces.append(rook);

}

void Move::undoCastleQueenside(QList<Piece> &pieces) const
{
    Piece rook;
    Position rookPosition(1, 4);

    if (!piece.isWhite())
    {
        rookPosition.row = 8;
    }
    rook = Piece::findPiece(rookPosition, pieces);

    Position kingNextPosition(piece.position.row, piece.position.column - 2);
    Position rookPreviousPosition(rookPosition.row, rookPosition.column - 3);

    Piece pieceAfterMove(piece);
    pieceAfterMove.position = kingNextPosition;
    pieces.removeAll(pieceAfterMove);
    pieces.removeAll(rook);


    pieces.append(piece);
    rook.position = rookPreviousPosition;
    pieces.append(rook);

}

bool Move::canCastleKingside(const QList<Piece> &pieces) const
{
    // TODO
    return true;
}

bool Move::canCastleQueenside(const QList<Piece> &pieces) const
{
    // TODO
    return true;
}
