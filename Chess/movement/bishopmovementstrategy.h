#ifndef BISHOPMOVEMENTSTRATEGY_H
#define BISHOPMOVEMENTSTRATEGY_H

#include "movementstrategy.h"

class BishopMovementStrategy : public MovementStrategy
{
public:

    /*
    * Constructor
    */
    BishopMovementStrategy();

    /*
    * @param position the position of the piece
    * @param targetPosition the target position of the piece
    * @param QMap<Position, Piece>: a map of the pieces on the board that use the position as key
    * @raise nothing
    * @return true if the piece can go to the target position, false otherwise
    */
    bool canGoTo(const Position &position, const Position &targetPosition, const QMap<Position, Piece> &pieces);

private:
    bool noBlockingPieceOnPath(const Position &position, const Position &targetPosition, const QMap<Position, Piece> &pieces);
};

#endif // BISHOPMOVEMENTSTRATEGY_H
