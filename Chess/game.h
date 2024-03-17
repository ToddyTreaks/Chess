#ifndef GAME_H
#define GAME_H

#include <QString>
#include <QFile>
#include <QDateTime>
#include <QList>

#include "move.h"

class Game
{
public:
    Game();
    QString nameWhite;
    QString nameBlack;
    QDateTime date;
    QString place;
    QString result;
    QList<Move> moves;

    void toPGN(QFile file);
};

#endif // GAME_H
