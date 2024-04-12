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

    QList<Move> readPgn(QFile &file) const;

private:
    static const unsigned int MAX_PGN_CHARACTERS = 32768;

    void parsePgn(QString fileContent, QList<Move> &moves) const;
    bool isEndingIndication(const QString &pgnInstruction) const;
    bool isMoveNumber(const QString &pgnInstruction) const;
    void instanciateMoves(const QString &pgnInstruction, const bool &whiteToPlay, QList<Move> &moves, QList<Piece> &pieces) const;
    Position getPrerequisite(QString pgnInstruction) const;
    Position getNextPosition(QString pgnInstruction) const;
    bool isValidPieceInput(const QChar &pgnChar) const;
    bool isValidRowInput(const QChar &pgnChar) const;
    bool isValidColumnInput(const QChar &pgnChar) const;
    int rowNumber(const QChar &rowInput) const;
    int columnNumber(const QChar &columnInput) const;
    bool isCapture(const QString &pgnInstruction) const;
    bool isPromotion(const QString &pgnInstruction) const;
    QString getPiecePromotedToPgnIdentifier(QString pgnInstruction) const;
};

#endif // PGNREADER_H
