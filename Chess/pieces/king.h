#ifndef KING_H
#define KING_H

#include "../piece.h"

class King : public Piece
{
public:
    King();
    King(QString color, Position position);

    virtual bool canGoTo(Position targetPosition, const QMap<Position, Piece> &pieces) override;
};

#endif // KING_H
