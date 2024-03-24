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
    GameManager(QString fileName);
    GameManager(QFile file);

    void toPgn(QFile file);

private:
    Board board;
    QList<Move> moves;
    QMap<Position, Piece*> pieces;
    QList<Piece> takenPieces;

    void createStartingPieces();

    void parsePgn(QString fileLine);
    bool isEndingIndication(QString pgnInstruction);
    bool isMoveNumber(QString pgnInstruction);
    void instanciateNewMove(QString pgnInstruction, QString color);
    Position getPrerequisite(QString pgnInstruction);
    Position getNextPosition(QString pgnInstruction);
    bool isValidPieceInput(QChar pgnChar);
    bool isValidRowInput(QChar pgnChar);
    bool isValidColumnInput(QChar pgnChar);
    int rowNumber(QChar rowInput);
    int columnNumber(QChar columnInput);
};

#endif // GAMEMANAGER_H
