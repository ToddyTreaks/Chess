#ifndef MOVEMENTSTRATEGY_H
#define MOVEMENTSTRATEGY_H

#include "../piece.h"

class MovementStrategy
{
public:

    /*
    * Constructor
    */
    MovementStrategy();
    
    /*
    * Destructor
    */
    ~MovementStrategy();

    /*
    * @param position the position of the piece
    * @param targetPosition the target position of the piece
    * @param QMap<Position, Piece>: a map of the pieces on the board that use the position as key
    * @raise nothing
    * @return true if the piece can go to the target position, false otherwise
    */
    virtual bool canGoTo(const Position &position, const Position &targetPosition, const QMap<Position, Piece> &pieces) = 0;
};

#endif // MOVEMENTSTRATEGY_H
