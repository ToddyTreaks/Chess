#ifndef MOVES_H
#define MOVES_H

#include <QList>
#include <QString>

#include "move.h"

class Moves
{
public:
    Moves();

    void addMove(Move newMove);
    void deleteLastMove();
    QString toString();

private:
    QList<Move> moves;
};

#endif // MOVES_H
