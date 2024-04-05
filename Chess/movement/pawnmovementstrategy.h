#ifndef PAWNMOVEMENTSTRATEGY_H
#define PAWNMOVEMENTSTRATEGY_H

#include "movementstrategy.h"

class PawnMovementStrategy : public MovementStrategy
{
public:

    /*
    * Constructor
    */
    PawnMovementStrategy();

    /*
    * @param position the position of the piece
    * @param targetPosition the target position of the piece
    * @param QMap<Position, Piece>: a map of the pieces on the board that use the position as key
    * @raise nothing
    * @return true if the piece can go to the target position, false otherwise
    */
    bool canGoTo(const Position &position, const Position &targetPosition, const QMap<Position, Piece> &pieces);
};

#endif // PAWNMOVEMENTSTRATEGY_H
