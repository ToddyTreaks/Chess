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
    Game(QFile file);

    QString nameWhite;
    QString nameBlack;
    QDateTime date;
    QString place;
    QString result;
    QList<Move> moves;

    void toPGN(QFile file);

private:
    static const long MAX_PGN_CHARACTERS = 1024;

    void parsePGN(QString fileContent);
};

#endif // GAME_H
