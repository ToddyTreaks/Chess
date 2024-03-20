#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QString>
#include <QFile>
#include <QDateTime>
#include <QList>

#include "move.h"
#include "board.h"
#include "position.h"

class GameManager
{
public:
    GameManager();
    GameManager(QFile file);

    void toPgn(QFile file);

private:
    Board board;
    QList<Move> moves;
    QList<Piece> pieces;
    QList<Piece> takenPieces;

    void parsePgn(QString fileLine);
    bool isEndingIndication(QString pgnInstruction);
    bool isMoveNumber(QString pgnInstruction);
    void instanciateNewMove(QString pgnInstruction);
    Position getPrerequisite(QString pgnInstruction);
    Position getNextPosition(QString pgnInstruction);
};

#endif // GAMEMANAGER_H
