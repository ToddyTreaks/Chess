#ifndef MOVE_H
#define MOVE_H

#include <QString>

#include "position.h"
#include "piece.h"

class Move
{
public:
    Move();
    Move(Piece piece, Position nextPosition);
    Move(Piece piece, Position previousPosition, Position nextPosition);

    QString toString();

    Piece getPiece();
    Position getPreviousPosition();
    Position getNextPosition();

    bool isCapture();
    Piece getCapturedPiece();
    bool isPromotion();
    Piece getPiecePromotedTo();

    bool isCastlingKingside();
    bool isCastlingQueenside();

    void setCapturedPiece(Piece capturedPiece);
    void setPiecePromotedTo(QString piecePromotedToIdentifier);
    void setKingsideCastlingKing(Piece castlingKing);
    void setQueensideCastlingKing(Piece castlingKing);

    void castleKingside(QMap<Position, Piece> &pieces);
    void castleQueenside(QMap<Position, Piece> &pieces);
    void undoCastleKingside(QMap<Position, Piece> &pieces);
    void undoCastleQueenside(QMap<Position, Piece> &pieces);
    bool canCastleKingside(const QMap<Position, Piece> &pieces);
    bool canCastleQueenside(const QMap<Position, Piece> &pieces);

private:
    Piece piece;
    Position previousPosition;
    Position nextPosition;

    bool capture;
    Piece capturedPiece;
    bool promotion;
    Piece piecePromotedTo;
    bool castlingKingside;
    bool castlingQueenside;
};

#endif // MOVE_H
