#ifndef MOVE_H
#define MOVE_H

#include <QString>

#include "position.h"
#include "piece.h"

class Move
{
public:
    Move();
    Move(const Piece &piece, const Position &nextPosition);
    Move(const Piece &piece, const Position &previousPosition, const Position &nextPosition);

    QString toString() const;

    Piece getPiece() const;
    Position getPreviousPosition() const;
    Position getNextPosition() const;

    bool isCapture() const;
    Piece getCapturedPiece() const;
    bool isPromotion() const;
    Piece getPiecePromotedTo() const;

    bool isCastlingKingside() const;
    bool isCastlingQueenside() const;

    void setCapturedPiece(Piece capturedPiece);
    void setPiecePromotedTo(QString piecePromotedToIdentifier);
    void setKingsideCastlingKing(Piece castlingKing);
    void setQueensideCastlingKing(Piece castlingKing);

    void applyMove(QList<Piece> &pieces) const;
    void undoMove(QList<Piece> &pieces) const;

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

    void castleKingside(QList<Piece> &pieces) const;
    void castleQueenside(QList<Piece> &pieces) const;
    void undoCastleKingside(QList<Piece> &pieces) const;
    void undoCastleQueenside(QList<Piece> &pieces) const;
    bool canCastleKingside(const QList<Piece> &pieces) const;
    bool canCastleQueenside(const QList<Piece> &pieces) const;
};

#endif // MOVE_H
