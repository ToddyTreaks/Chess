#include "gamemanager.h"

#include <QTextStream>
#include <QDebug>

#include "pieces/bishop.h"
#include "pieces/king.h"
#include "pieces/knight.h"
#include "pieces/pawn.h"
#include "pieces/queen.h"
#include "pieces/rook.h"

GameManager::GameManager() {}

GameManager::GameManager(QString fileName)
    : GameManager(QFile(fileName))
{}

GameManager::GameManager(QFile file)
{
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }

    QTextStream stream(&file);
    QString fileLine;
    while (stream.readLineInto(&fileLine))
    {
        parsePgn(fileLine);
    }

    qDebug() << "Moves :";
    QListIterator iterator(moves);
    while (iterator.hasNext())
    {
        Move move = iterator.next();
        qDebug() << move.toString();
    }
}

void GameManager::parsePgn(QString fileLine)
{
    qDebug() << fileLine;

    createStartingPieces();

    QStringList pgnInstructions;
    pgnInstructions = fileLine.split(" ");

    QString color = "White";

    QListIterator iterator(pgnInstructions);
    while (iterator.hasNext())
    {
        QString pgnInstruction = iterator.next();

        if (!isEndingIndication(pgnInstruction) && !isMoveNumber(pgnInstruction))
        {
            instanciateNewMove(pgnInstruction, color);
        }

        if (color == "White")
        {
            color = "Black";
        }
        else
        {
            color = "White";
        }

    }

}

void GameManager::createStartingPieces()
{
    pieces.insert(Position(5, 1), King("White", Position(5, 1)));
    pieces.insert(Position(4, 1), Queen("White", Position(4, 1)));
    pieces.insert(Position(3, 1), Bishop("White", Position(3, 1)));
    pieces.insert(Position(6, 1), Bishop("White", Position(6, 1)));
    pieces.insert(Position(2, 1), Knight("White", Position(2, 1)));
    pieces.insert(Position(7, 1), Knight("White", Position(7, 1)));
    pieces.insert(Position(1, 1), Rook("White", Position(1, 1)));
    pieces.insert(Position(8, 1), Rook("White", Position(8, 1)));

    for (int i=0; i<8; i++)
    {
        pieces.insert(Position(i+1, 2), Pawn("White", Position(i+1, 2)));
    }

    pieces.insert(Position(5, 8), King("Black", Position(5, 8)));
    pieces.insert(Position(4, 8), Queen("Black", Position(4, 8)));
    pieces.insert(Position(3, 8), Bishop("Black", Position(3, 8)));
    pieces.insert(Position(6, 8), Bishop("Black", Position(6, 8)));
    pieces.insert(Position(2, 8), Knight("Black", Position(2, 8)));
    pieces.insert(Position(7, 8), Knight("Black", Position(7, 8)));
    pieces.insert(Position(1, 8), Rook("Black", Position(1, 8)));
    pieces.insert(Position(8, 8), Rook("Black", Position(8, 8)));

    for (int i=0; i<8; i++)
    {
        pieces.insert(Position(i+1, 7), Pawn("Black", Position(i+1, 7)));
    }
    return;
}

bool GameManager::isEndingIndication(QString pgnInstruction)
{
    QStringList possibleFisrtTwoLetters = {"1/", "1-", "0-"};
    QString instructionFirstTwoLetters = pgnInstruction.first(2);
    return possibleFisrtTwoLetters.contains(instructionFirstTwoLetters);
}

bool GameManager::isMoveNumber(QString pgnInstruction)
{
    return (pgnInstruction.last(1) == ".");
}

void GameManager::instanciateNewMove(QString pgnInstruction, QString color)
{
    if (pgnInstruction.size() < 1)
    {
        // TODO error
        return;
    }
    QChar firstLetter;
    firstLetter = pgnInstruction.at(0);

    if (firstLetter == 'O')
    {
        if (pgnInstruction == "O-O-O")
        {
            // TODO
            return;
        }

        if(pgnInstruction == "O-O")
        {
            // TODO
            return;
        }

        //TODO
        return;
    }

    Position prerequisite = getPrerequisite(pgnInstruction);
    Position nextPosition = getNextPosition(pgnInstruction);

    if (isValidPieceInput(firstLetter))
    {
        Move newMove(Piece::findPiece((QString) firstLetter, color, nextPosition, prerequisite, pieces), nextPosition);
    }
    Move newMove(Piece::findPiece("", color, nextPosition, prerequisite, pieces), nextPosition);
    moves.append(newMove);

    return;

}

Position GameManager::getPrerequisite(QString pgnInstruction)
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

Position GameManager::getNextPosition(QString pgnInstruction)
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

bool GameManager::isValidPieceInput(QChar pgnChar)
{
    QList<QChar> validPieceInputList = { 'K', 'Q', 'B', 'N', 'R'};
    return (validPieceInputList.contains(pgnChar));
}

bool GameManager::isValidRowInput(QChar pgnChar)
{
    return ('a' <= pgnChar && pgnChar <= 'h');
}

bool GameManager::isValidColumnInput(QChar pgnChar)
{
    return ('1' <= pgnChar && pgnChar <= '8');
}

int GameManager::rowNumber(QChar rowInput)
{
    return rowInput.unicode() - QChar('1').unicode() + 1;
}

int GameManager::columnNumber(QChar columnInput)
{
    return columnInput.unicode() - QChar('a').unicode() + 1;
}


