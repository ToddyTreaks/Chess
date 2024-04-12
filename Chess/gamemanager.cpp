#include "gamemanager.h"

#include <QDebug>

GameManager::GameManager() {}

GameManager::GameManager(QString fileName)
    : GameManager(QFile(fileName))
{}

GameManager::GameManager(QFile file)
    : pgnReader()
{
    nextMoves = pgnReader.readPgn(file);
    pieces = Piece::createStartingPieces();
}

const QList<Piece> GameManager::getPieces()
{
    return pieces;
}

void GameManager::nextMove()
{
    if (nextMoves.isEmpty())
    {
        // TODO error
        return;
    }

    Move nextMove = nextMoves.takeFirst();
    nextMove.applyMove(pieces);

    movesDone.prepend(nextMove);
}

void GameManager::previousMove()
{
    if (movesDone.isEmpty())
    {
        // TODO error
        return;
    }

    Move previousMove = movesDone.takeFirst();
    previousMove.undoMove(pieces);

    nextMoves.prepend(previousMove);
}

bool GameManager::hasNextMove()
{
    return !nextMoves.isEmpty();
}

bool GameManager::hasPreviousMove()
{
    return !movesDone.isEmpty();
}
