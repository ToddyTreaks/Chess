#ifndef MOVEMENTSTRATEGY_H
#define MOVEMENTSTRATEGY_H

#include "../piece.h"

class MovementStrategy
{
public:
    MovementStrategy();
    ~MovementStrategy();

    virtual bool canGoTo(const Position &position, const Position &targetPosition, const QMap<Position, Piece> &pieces) = 0;
};

#endif // MOVEMENTSTRATEGY_H
