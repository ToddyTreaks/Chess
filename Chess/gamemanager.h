#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QString>
#include <QFile>
#include <QList>

#include "move.h"
#include "position.h"

class GameManager
{
public:
    GameManager();
    GameManager(QString fileName);
    GameManager(QFile file);

    const QMap<Position, Piece> getPieces();

    void nextMove();
    void previousMove();

    bool hasNextMove();
    bool hasPreviousMove();

    void toPgn(QFile file);

private:
    QList<Move> nextMoves;
    QList<Move> movesDone;
    QMap<Position, Piece> pieces;
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
    bool isCapture(QString pgnInstruction);
    bool isPromotion(QString pgnInstruction);
    QString getPiecePromotedToPgnIdentifier(QString pgnInstruction);
};

#endif // GAMEMANAGER_H
