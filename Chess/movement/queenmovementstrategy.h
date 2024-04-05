#ifndef QUEEN_H
#define QUEEN_H

#include "movementstrategy.h"

class QueenMovementStrategy : public MovementStrategy
{
public:

    /*
    * Constructor
    */
    QueenMovementStrategy();

    /*
    * @param position the position of the piece
    * @param targetPosition the target position of the piece
    * @param QMap<Position, Piece>: a map of the pieces on the board that use the position as key
    * @raise nothing
    * @return true if the piece can go to the target position, false otherwise
    */
    bool canGoTo(const Position &position, const Position &targetPosition, const QMap<Position, Piece> &pieces);
};

#endif // QUEEN_H
