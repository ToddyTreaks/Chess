#ifndef BISHOP_H
#define BISHOP_H

#include "../piece.h"

class Bishop : public Piece
{
public:
    Bishop();
    Bishop(QString color, Position position);

    bool canGoTo(Position targetPosition, const QMap<Position, Piece*> &pieces);
};

#endif // BISHOP_H
