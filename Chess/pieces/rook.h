#ifndef ROOK_H
#define ROOK_H

#include "../piece.h"

class Rook : Piece
{
public:
    Rook();
    virtual bool canGoTo(Position targetPosition, const QMap<Position, Piece> &pieces) override;
};

#endif // ROOK_H
