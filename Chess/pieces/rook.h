#ifndef ROOK_H
#define ROOK_H

#include "../piece.h"

class Rook : public Piece
{
public:
    Rook();
    Rook(const Piece &piece);
    Rook(QString color, Position position);

    bool canGoTo(const Position &targetPosition, const QMap<Position, Piece*> &pieces);

private:
    bool noBlockingPieceOnColumn(const Position &targetPosition, const QMap<Position, Piece*> &pieces);
    bool noBlockingPieceOnRow(const Position &targetPosition, const QMap<Position, Piece*> &pieces);

};

#endif // ROOK_H
