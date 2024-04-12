#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QList>

#include "move.h"
#include "position.h"
#include "pgnreader.h"

class GameManager
{
public:
    GameManager();
    GameManager(const QString &fileName);
    GameManager(QFile file);

    const QList<Piece> getPieces() const;

    void nextMove();
    void previousMove();

    bool hasNextMove() const;
    bool hasPreviousMove() const;

    void toPgn(QFile file) const;

private:
    QList<Move> nextMoves;
    QList<Move> movesDone;
    QList<Piece> pieces;

    PgnReader pgnReader;
};

#endif // GAMEMANAGER_H
