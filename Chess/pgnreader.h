#ifndef PGNREADER_H
#define PGNREADER_H

#include <QString>
#include <QList>

#include "move.h"
#include "position.h"

class PgnReader
{
public:
    PgnReader();

    QList<Move> readPgn(QFile &file);

private:
    static const unsigned int MAX_PGN_CHARACTERS = 32768;

    void parsePgn(QString fileContent, QList<Move> &moves);
    bool isEndingIndication(QString pgnInstruction);
    bool isMoveNumber(QString pgnInstruction);
    void instanciateMoves(QString pgnInstruction, bool whiteToPlay, QList<Move> &moves, QList<Piece> &pieces);
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

#endif // PGNREADER_H
