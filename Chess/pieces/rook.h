#ifndef ROOK_H
#define ROOK_H

#include "../piece.h"

class Rook : public Piece
{
public:
    Rook();
    Rook(QString color, Position position);

    virtual bool canGoTo(Position targetPosition, const QMap<Position, Piece> &pieces) override;
};

#endif // ROOK_H
