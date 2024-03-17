#ifndef GAME_H
#define GAME_H

#include <QString>
#include <QFile>
#include <QDateTime>

#include "moves.h"

class Game
{
public:
    Game();
    QString nameWhite;
    QString nameBlack;
    QDateTime date;
    QString place;
    QString result;
    Moves moves;

    void toPGN(QFile file);
};

#endif // GAME_H
