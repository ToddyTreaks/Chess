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
    bool isCastlingQueenside() const;

    void setCapturedPiece(Piece capturedPiece);
    void setPiecePromotedTo(QString piecePromotedToIdentifier);
    void setKingsideCastlingKing(Piece castlingKing);
    void setQueensideCastlingKing(Piece castlingKing);

    void castleKingside(QList<Piece> &pieces);
    void castleQueenside(QList<Piece> &pieces);
    void undoCastleKingside(QList<Piece> &pieces);
    void undoCastleQueenside(QList<Piece> &pieces);
    bool canCastleKingside(const QList<Piece> &pieces);
    bool canCastleQueenside(const QList<Piece> &pieces);

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

    void initializeAttributes();
};

#endif // MOVE_H
