#ifndef KNIGHT_H
#define KNIGHT_H

#include "../piece.h"

class Knight : public Piece
{
public:
    Knight();
    Knight(QString color, Position position);

    bool canGoTo(Position targetPosition, const QMap<Position, Piece*> &pieces);
};

#endif // KNIGHT_H
