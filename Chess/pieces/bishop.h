#ifndef BISHOP_H
#define BISHOP_H

#include "../piece.h"

class Bishop : Piece
{
public:
    Bishop();
    virtual bool canGoTo(Position targetPosition, const QMap<Position, Piece> &pieces) override;
};

#endif // BISHOP_H
