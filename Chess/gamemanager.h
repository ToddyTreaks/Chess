#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QString>
#include <QFile>
#include <QDateTime>
#include <QList>

#include "move.h"
#include "position.h"

class GameManager
{
public:
    GameManager();
    GameManager(QString fileName);
    GameManager(QFile file);

    void nextMove();
    void previousMove();

    void toPgn(QFile file);

private:
    QList<Move> nextMoves;
    QList<Move> movesDone;
    QMap<Position, Piece*> pieces;
    QList<Piece> takenPieces;

    const unsigned int MAX_PGN_CHARACTERS = 32768;

    void createStartingPieces();
    void parsePgn(QString fileContent);
    bool isEndingIndication(QString pgnInstruction);
    bool isMoveNumber(QString pgnInstruction);
    void instanciateMoves(QString pgnInstruction, QString color);
    Position getPrerequisite(QString pgnInstruction);
    Position getNextPosition(QString pgnInstruction);
    bool isValidPieceInput(QChar pgnChar);
    bool isValidRowInput(QChar pgnChar);
    bool isValidColumnInput(QChar pgnChar);
    int rowNumber(QChar rowInput);
    int columnNumber(QChar columnInput);
};

#endif // GAMEMANAGER_H
