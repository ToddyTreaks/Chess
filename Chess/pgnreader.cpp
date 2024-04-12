#include "pgnreader.h"

#include <QTextStream>
#include <QDebug>

PgnReader::PgnReader() {}

QList<Move> PgnReader::readPgn(QFile &file)
{
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        // TODO error
        return QList<Move>();
    }

    QList<Move> moves;

    QTextStream stream(&file);
    QString fileContent = stream.read(MAX_PGN_CHARACTERS);

    parsePgn(fileContent, moves);

    return moves;
}

void PgnReader::parsePgn(QString fileContent, QList<Move> &moves)
{
    fileContent.replace('\n', ' ');
    QStringList pgnInstructions;
    pgnInstructions = fileContent.split(' ');

    bool whiteToPlay = true;
    QList<Piece> pieces = Piece::createStartingPieces();

    QListIterator iterator(pgnInstructions);
    while (iterator.hasNext())
    {
        QString pgnInstruction = iterator.next();

        if (!isEndingIndication(pgnInstruction) && !isMoveNumber(pgnInstruction))
        {
            instanciateMoves(pgnInstruction, whiteToPlay, moves, pieces);
            whiteToPlay = !whiteToPlay;
        }

    }

}

bool PgnReader::isEndingIndication(QString pgnInstruction)
{
    if (pgnInstruction.size() < 2)
    {
        return false;
    }

    QStringList possibleFisrtTwoLetters = {"1/", "1-", "0-"};
    QString instructionFirstTwoLetters = pgnInstruction.first(2);
    return possibleFisrtTwoLetters.contains(instructionFirstTwoLetters);
}

bool PgnReader::isMoveNumber(QString pgnInstruction)
{
    if (pgnInstruction.isEmpty())
    {
        return false;
    }
    return (pgnInstruction.last(1) == ".");
}

void PgnReader::instanciateMoves(QString pgnInstruction, bool whiteToPlay, QList<Move> &moves, QList<Piece> &pieces)
{
    Move newMove;

    if (pgnInstruction.size() < 1)
    {
        // TODO error
        return;
    }
    QChar firstLetter;
    firstLetter = pgnInstruction.at(0);

    Position prerequisite = getPrerequisite(pgnInstruction);
    Position nextPosition = getNextPosition(pgnInstruction);

    if (firstLetter == 'O')
    {
        Piece castlingKing = Piece::findPiece("K", whiteToPlay, pieces);
        qDebug() << castlingKing.toString();
        if (pgnInstruction == "O-O-O")
        {
            newMove.setQueensideCastlingKing(castlingKing);
        }

        if(pgnInstruction == "O-O")
        {
            newMove.setKingsideCastlingKing(castlingKing);
        }
    }
    else if (isValidPieceInput(firstLetter))
    {
        newMove = Move(Piece::findPiece((QString) firstLetter, whiteToPlay, nextPosition, prerequisite, pieces), nextPosition);
    }
    else
    {
        newMove = Move(Piece::findPiece("", whiteToPlay, nextPosition, prerequisite, pieces), nextPosition);
    }

    if (isCapture(pgnInstruction))
    {
        newMove.setCapturedPiece(Piece::findPiece(nextPosition, pieces));
    }

    if (isPromotion(pgnInstruction))
    {
        newMove.setPiecePromotedTo(getPiecePromotedToPgnIdentifier(pgnInstruction));
    }

    newMove.applyMove(pieces);
    moves.append(newMove);
}

Position PgnReader::getPrerequisite(QString pgnInstruction)
{
    if (!isValidPieceInput(pgnInstruction.at(0)))
    {
        pgnInstruction = pgnInstruction.sliced(1);
    }

    Position prerequisitePosition(0, 0);
    if (pgnInstruction.size() < 2)
    {
        // TODO error
        return prerequisitePosition;
    }
    QChar firstLetter, secondLetter, thirdLetter;
    firstLetter = pgnInstruction.at(0);
    secondLetter = pgnInstruction.at(1);

    if (firstLetter.isLetter() && firstLetter != 'x' && secondLetter == 'x' || secondLetter.isNumber())
    {
        prerequisitePosition.column = firstLetter.digitValue() - QChar('a').digitValue();
        return prerequisitePosition;
    }

    if (firstLetter.isNumber() && secondLetter.isLetter())
    {
        prerequisitePosition.row = firstLetter.digitValue() - QChar('1').digitValue();
        return prerequisitePosition;
    }

    if (pgnInstruction.size() < 3)
    {
        return prerequisitePosition;
    }

    secondLetter = pgnInstruction.at(2);
    if (firstLetter.isLetter() && secondLetter.isNumber() && secondLetter.isLetter())
    {
        prerequisitePosition.column = firstLetter.digitValue() - QChar('a').digitValue();
        prerequisitePosition.row = firstLetter.digitValue() - QChar('1').digitValue();
        return prerequisitePosition;
    }

    // TODO error
    return prerequisitePosition;
}

Position PgnReader::getNextPosition(QString pgnInstruction)
{
    Position position(0, 0);
    while (pgnInstruction.size() > 2 && !isValidColumnInput(pgnInstruction.back()))
    {
        pgnInstruction.removeLast();
    }
    if (pgnInstruction.size() == 0)
    {
        //TODO error
        return position;
    }

    position.row =  rowNumber(pgnInstruction.back());
    pgnInstruction.removeLast();
    position.column =  columnNumber(pgnInstruction.back());
    return position;
}

bool PgnReader::isValidPieceInput(QChar pgnChar)
{
    QList<QChar> validPieceInputList = { 'K', 'Q', 'B', 'N', 'R'};
    return (validPieceInputList.contains(pgnChar));
}

bool PgnReader::isValidRowInput(QChar pgnChar)
{
    return ('a' <= pgnChar && pgnChar <= 'h');
}

bool PgnReader::isValidColumnInput(QChar pgnChar)
{
    return ('1' <= pgnChar && pgnChar <= '8');
}

int PgnReader::rowNumber(QChar rowInput)
{
    return rowInput.unicode() - QChar('1').unicode() + 1;
}

int PgnReader::columnNumber(QChar columnInput)
{
    return columnInput.unicode() - QChar('a').unicode() + 1;
}

bool PgnReader::isCapture(QString pgnInstruction)
{
    return pgnInstruction.contains('x');
}

bool PgnReader::isPromotion(QString pgnInstruction)
{
    return pgnInstruction.contains('=');
}

QString PgnReader::getPiecePromotedToPgnIdentifier(QString pgnInstruction)
{
    while (pgnInstruction.size() > 1 && pgnInstruction.front() != '=')
    {
        pgnInstruction.removeFirst();
    }

    if (pgnInstruction.size() <= 1)
    {
        //TODO error
        return "";
    }

    return pgnInstruction[1];
}
