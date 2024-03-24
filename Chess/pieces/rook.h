#ifndef ROOK_H
#define ROOK_H

#include "../piece.h"

class Rook : public Piece
{
public:
    Rook();
    Rook(QString color, Position position);

    bool canGoTo(Position targetPosition, const QMap<Position, Piece*> &pieces);
};

#endif // ROOK_H
