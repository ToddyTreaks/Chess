#ifndef MOVE_H
#define MOVE_H

#include <QString>

#include "position.h"
#include "piece.h"

class Move
{
public:
    Move();
    QString toString();

private:
    Position next;
    Piece piece;
};

#endif // MOVE_H
