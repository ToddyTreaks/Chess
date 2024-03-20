#ifndef KING_H
#define KING_H

#include "../piece.h"

class King : Piece
{
public:
    King();
    virtual bool canGoTo(Position targetPosition, const QMap<Position, Piece> &pieces) override;
};

#endif // KING_H
