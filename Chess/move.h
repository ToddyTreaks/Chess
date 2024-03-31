#ifndef MOVE_H
#define MOVE_H

#include <QString>

#include "position.h"
#include "piece.h"

class Move
{
public:
    Move();
    Move(Piece* piece, Position nextPosition);
    Move(Piece* piece, Position previousPosition, Position nextPosition);

    QString toString();

    Piece* getPiece();
    Position getPreviousPosition();
    Position getNextPosition();
    Piece* getCapturedPiece();
    bool isCapture();
    bool isCastlingKingside();
    bool isCastlingQueenside();

    void setCapturedPiece(Piece* capturedPiece);
    void setKingsideCastlingKing(Piece* castlingKing);
    void setQueensideCastlingKing(Piece* castlingKing);

private:
    Piece* piece;
    Position previousPosition;
    Position nextPosition;
    bool capture;
    Piece* capturedPiece;
    bool castlingKingside;
    bool castlingQueenside;
};

#endif // MOVE_H
