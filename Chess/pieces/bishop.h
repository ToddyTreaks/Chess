#ifndef BISHOP_H
#define BISHOP_H

#include "../piece.h"

class Bishop : public Piece
{
public:
    Bishop();
    Bishop(const Piece &piece);
    Bishop(QString color, Position position);

    bool canGoTo(const Position &targetPosition, const QMap<Position, Piece*> &pieces);

private:
    bool noBlockingPieceOnPath(const Position &targetPosition, const QMap<Position, Piece*> &pieces);
};

#endif // BISHOP_H
