#include "move.h"

Move::Move() {}

Move::Move(Piece piece, Position nextPosition)
    : piece(piece), nextPosition(nextPosition)
{}


