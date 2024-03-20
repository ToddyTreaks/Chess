#ifndef KNIGHT_H
#define KNIGHT_H

#include "../piece.h"

class Knight : Piece
{
public:
    Knight();
    virtual bool canGoTo(Position targetPosition, const QMap<Position, Piece> &pieces) override;
};

#endif // KNIGHT_H
