#ifndef KING_H
#define KING_H

#include "../piece.h"

class King : public Piece
{
public:
    King();
    King(QString color, Position position);

    bool canGoTo(const Position &targetPosition, const QMap<Position, Piece*> &pieces);

};

#endif // KING_H
