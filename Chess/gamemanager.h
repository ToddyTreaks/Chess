#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QList>

#include "board.h"
#include "move.h"

class GameManager
{
public:
    GameManager();
    GameManager(QList<Move> gameMoves);

    void nextMove();
    void previousMove();
    void drawBoard();

private:
    Board board;
    QList<Move> previousMoves;
    QList<Move> nextMoves;
};

#endif // GAMEMANAGER_H
