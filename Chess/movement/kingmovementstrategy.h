#ifndef KINGMOVEMENTSTRATEGY_H
#define KINGMOVEMENTSTRATEGY_H

#include "movementstrategy.h"

class KingMovementStrategy : public MovementStrategy
{
public:

    /*
    * Constructor
    */
    KingMovementStrategy();

    /*
    * @param position the position of the piece
    * @param targetPosition the target position of the piece
    * @param QMap<Position, Piece>: a map of the pieces on the board that use the position as key
    * @raise nothing
    * @return true if the piece can go to the target position, false otherwise
    */
    bool canGoTo(const Position &position, const Position &targetPosition, const QMap<Position, Piece> &pieces);
};

#endif // KINGMOVEMENTSTRATEGY_H
