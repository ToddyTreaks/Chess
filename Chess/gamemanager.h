#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QString>
#include <QFile>
#include <QList>

#include "move.h"
#include "position.h"
#include "pgnreader.h"

class GameManager
{
public:
    GameManager();
    GameManager(QString fileName);
    GameManager(QFile file);

    const QList<Piece> getPieces();

    void nextMove();
    void previousMove();

    bool hasNextMove();
    bool hasPreviousMove();

    void toPgn(QFile file);

private:
    QList<Move> nextMoves;
    QList<Move> movesDone;
    QList<Piece> pieces;

    PgnReader pgnReader;
};

#endif // GAMEMANAGER_H
