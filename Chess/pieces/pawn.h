#ifndef PAWN_H
#define PAWN_H

#include "../piece.h"

class Pawn : Piece
{
public:
    Pawn();
    virtual bool canGoTo(Position targetPosition, const QMap<Position, Piece> &pieces) override;
};

#endif // PAWN_H
