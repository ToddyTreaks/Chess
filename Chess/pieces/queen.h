#ifndef QUEEN_H
#define QUEEN_H

#include "../piece.h"

class Queen : Piece
{
public:
    Queen();
    virtual bool canGoTo(Position targetPosition, const QMap<Position, Piece> &pieces) override;
};

#endif // QUEEN_H
