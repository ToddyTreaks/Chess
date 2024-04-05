#ifndef MOVEMENTSTRATEGY_H
#define MOVEMENTSTRATEGY_H

#include "../piece.h"

class MovementStrategy
{
public:
    MovementStrategy();
    ~MovementStrategy();

    virtual bool canGoTo(const Position &position, const Position &targetPosition, const QList<Piece> &pieces) = 0;
};

#endif // MOVEMENTSTRATEGY_H
