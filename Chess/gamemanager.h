#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "board.h"
#include "moves.h"

class GameManager
{
public:
    GameManager();

    void nextMove();
    void previousMove();
    void drawBoard();

private:
    Board actual;
    Moves moves;
};

#endif // GAMEMANAGER_H
