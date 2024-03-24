#ifndef BISHOP_H
#define BISHOP_H

#include "../piece.h"

class Bishop : public Piece
{
public:
    Bishop();
    Bishop(QString color, Position position);

    virtual bool canGoTo(Position targetPosition, const QMap<Position, Piece> &pieces) override;
};

#endif // BISHOP_H
