#include "moves.h"

Moves::Moves() {}

void Moves::addMove(Move newMove)
{
    moves.append(newMove);
}

void Moves::deleteLastMove()
{
    moves.removeLast();
}
