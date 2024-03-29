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

    createStartingPieces();

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

void GameManager::createStartingPieces()
{
    King* wKing = new King("White", Position(1, 5));
    pieces.insert(Position(1, 5), wKing);
    Queen* wQueen = new Queen("White", Position(1, 4));
    pieces.insert(Position(1, 4), wQueen);
    Bishop* wBishop1 = new Bishop("White", Position(1, 3));
    pieces.insert(Position(1, 3), wBishop1);
    Bishop* wBishop2 = new Bishop("White", Position(1, 6));
    pieces.insert(Position(1, 6), wBishop2);
    Knight* wKnight1 = new Knight("White", Position(1, 2));
    pieces.insert(Position(1, 2), wKnight1);
    Knight* wKnight2 = new Knight("White", Position(1, 7));
    pieces.insert(Position(1, 7), wKnight2);
    Rook* wRook1 = new Rook("White", Position(1, 1));
    pieces.insert(Position(1, 1), wRook1);
    Rook* wRook2 = new Rook("White", Position(1, 8));
    pieces.insert(Position(1, 8), wRook2);

    for (int i=0; i<8; i++)
    {
        Pawn* wPawn = new Pawn("White", Position(2, i+1));
        pieces.insert(Position(2, i+1), wPawn);
    }

    King* bKing = new King ("Black", Position(8, 5));
    pieces.insert(Position(8, 5), bKing);
    Queen* bQueen = new Queen ("Black", Position(8, 4));
    pieces.insert(Position(8, 4), bQueen);
    Bishop* bBishop1 = new Bishop ("Black", Position(8, 3));
    pieces.insert(Position(8, 3), bBishop1);
    Bishop* bBishop2 = new Bishop ("Black", Position(8, 6));
    pieces.insert(Position(8, 6), bBishop2);
    Knight* bKnight1 = new Knight ("Black", Position(8, 2));
    pieces.insert(Position(8, 2), bKnight1);
    Knight* bKnight2 = new Knight ("Black", Position(8, 7));
    pieces.insert(Position(8, 7), bKnight2);
    Rook* bRook1 = new Rook ("Black", Position(8, 1));
    pieces.insert(Position(8, 1), bRook1);
    Rook* bRook2 = new Rook ("Black", Position(8, 8));
    pieces.insert(Position(8, 8), bRook2);

    for (int i=0; i<8; i++)
    {
        Pawn* bPawn = new Pawn("Black", Position(7, i+1));
        pieces.insert(Position(7, i+1), bPawn);
    }
    return;
}

void GameManager::parsePgn(QString fileLine)
{
    qDebug() << fileLine;

    QStringList pgnInstructions;
    pgnInstructions = fileLine.split(" ");

    QString color = "White";

    QListIterator iterator(pgnInstructions);
    while (iterator.hasNext())
    {
        QString pgnInstruction = iterator.next();

        qDebug() << pgnInstruction;

        if (!isEndingIndication(pgnInstruction) && !isMoveNumber(pgnInstruction))
        {
            instanciateNewMove(pgnInstruction, color);

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
        moves.append(newMove);
    }
    else
    {
        Move newMove(Piece::findPiece("", color, nextPosition, prerequisite, pieces), nextPosition);
        moves.append(newMove);
    }

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


