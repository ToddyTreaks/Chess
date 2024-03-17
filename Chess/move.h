#ifndef MOVE_H
#define MOVE_H

#include <QString>

#include "position.h"
#include "piece.h"

class Move
{
public:
    Move();
    Move(Piece piece, Position nextPosition);

    QString toString();

private:
    Piece piece;
    Position nextPosition;
};

#endif // MOVE_H
