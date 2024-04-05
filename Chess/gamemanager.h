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
    /*
    * Constructors
    */
    GameManager();
    GameManager(QString fileName);
    GameManager(QFile file);
    
    /*
    * Attributes
    */
    const QMap<Position, Piece> getPieces();

    /*
    * @note goes to the next move in the list
    */
    void nextMove();

    /*
    * @note goes to the previous move in the list
    */
    void previousMove();

    /*
    * @return true if there is a next move, false otherwise
    */
    bool hasNextMove();

    /*
    * @return true if there is a previous move, false otherwise
    */
    bool hasPreviousMove();

    /*
    * @note transform the move list into a PGN file
    */
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
