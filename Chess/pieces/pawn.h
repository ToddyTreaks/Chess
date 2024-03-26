#ifndef PAWN_H
#define PAWN_H

#include "../piece.h"

class Pawn : public Piece
{
public:
    Pawn();
    Pawn(QString color, Position position);

    bool canGoTo(const Position &targetPosition, const QMap<Position, Piece*> &pieces);
};

#endif // PAWN_H
