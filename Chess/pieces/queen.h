#ifndef QUEEN_H
#define QUEEN_H

#include "../piece.h"

class Queen : public Piece
{
public:
    Queen();
    Queen(QString color, Position position);

    bool canGoTo(const Position &targetPosition, const QMap<Position, Piece*> &pieces);
};

#endif // QUEEN_H
