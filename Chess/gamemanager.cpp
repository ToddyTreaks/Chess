#include "gamemanager.h"

GameManager::GameManager() {}

GameManager::GameManager(QList<Move> gameMoves)
    : board(), previousMoves(), nextMoves(gameMoves)
{}

void GameManager::nextMove()
{
    if (nextMoves.isEmpty())
    {
        //TODO return error
        return;
    }

    Move next = nextMoves.first();

    nextMoves.removeFirst();
    previousMoves.prepend(next);

    board.update(next);
}

void GameManager::previousMove()
{
    if (previousMoves.isEmpty())
    {
        //TODO return error
        return;
    }

    Move previous = previousMoves.first();

    nextMoves.removeFirst();
    previousMoves.prepend(previous);

    board.updateBackwards(previous);
}
