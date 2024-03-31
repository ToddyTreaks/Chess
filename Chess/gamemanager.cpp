#include "gamemanager.h"

#include <QTextStream>
#include <QDebug>

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
    QString fileContent = stream.read(MAX_PGN_CHARACTERS);
    parsePgn(fileContent);
    while (hasPreviousMove())
    {
        qDebug() << "previousmove()";
        previousMove();
    }
}

void GameManager::createStartingPieces()
{
    pieces.insert(Position(1, 5), Piece("White", "K", Position(1, 5)));
    pieces.insert(Position(1, 4), Piece("White", "Q", Position(1, 4)));
    pieces.insert(Position(1, 3), Piece("White", "B", Position(1, 3)));
    pieces.insert(Position(1, 6), Piece("White", "B", Position(1, 6)));
    pieces.insert(Position(1, 2), Piece("White", "N", Position(1, 2)));
    pieces.insert(Position(1, 7), Piece("White", "N", Position(1, 7)));
    pieces.insert(Position(1, 1), Piece("White", "R", Position(1, 1)));
    pieces.insert(Position(1, 8), Piece("White", "R", Position(1, 8)));

    for (int i=0; i<8; i++)
    {
        pieces.insert(Position(2, i+1), Piece("White", "", Position(2, i+1)));
    }

    pieces.insert(Position(8, 5), Piece("Black", "K", Position(8, 5)));
    pieces.insert(Position(8, 4), Piece("Black", "Q", Position(8, 4)));
    pieces.insert(Position(8, 3), Piece("Black", "B", Position(8, 3)));
    pieces.insert(Position(8, 6), Piece("Black", "B", Position(8, 6)));
    pieces.insert(Position(8, 2), Piece("Black", "N", Position(8, 2)));
    pieces.insert(Position(8, 7), Piece("Black", "N", Position(8, 7)));
    pieces.insert(Position(8, 1), Piece("Black", "R", Position(8, 1)));
    pieces.insert(Position(8, 8), Piece("Black", "R", Position(8, 8)));

    for (int i=0; i<8; i++)
    {
        pieces.insert(Position(7, i+1), Piece("Black", "", Position(7, i+1)));
    }
}

void GameManager::parsePgn(QString fileContent)
{
    fileContent.replace('\n', ' ');
    QStringList pgnInstructions;
    pgnInstructions = fileContent.split(' ');

    QString color = "White";

    QListIterator iterator(pgnInstructions);
    while (iterator.hasNext())
    {
        QString pgnInstruction = iterator.next();

        qDebug() << "------------new instruction -----------------" << pgnInstruction;

        if (!isEndingIndication(pgnInstruction) && !isMoveNumber(pgnInstruction))
        {
            instanciateMoves(pgnInstruction, color);

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
    if (pgnInstruction.size() < 2)
    {
        return false;
    }

    QStringList possibleFisrtTwoLetters = {"1/", "1-", "0-"};
    QString instructionFirstTwoLetters = pgnInstruction.first(2);
    return possibleFisrtTwoLetters.contains(instructionFirstTwoLetters);
}

bool GameManager::isMoveNumber(QString pgnInstruction)
{
    if (pgnInstruction.isEmpty())
    {
        return false;
    }
    return (pgnInstruction.last(1) == ".");
}

void GameManager::instanciateMoves(QString pgnInstruction, QString color)
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
        Piece castlingKing = Piece::findPiece("K", color, pieces);
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
        newMove = Move(Piece::findPiece((QString) firstLetter, color, nextPosition, prerequisite, pieces), nextPosition);
    }
    else
    {
        newMove = Move(Piece::findPiece("", color, nextPosition, prerequisite, pieces), nextPosition);
    }

    if (isCapture(pgnInstruction))
    {
        newMove.setCapturedPiece(pieces.value(nextPosition));
    }

    nextMoves.append(newMove);

    nextMove();
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

bool GameManager::isCapture(QString pgnInstruction)
{
    return pgnInstruction.contains('x');
}

const QMap<Position, Piece> GameManager::getPieces()
{
    return pieces;
}

void GameManager::nextMove()
{
    if (nextMoves.isEmpty())
    {
        //TODO error
        return;
    }

    Move nextMove = nextMoves.takeFirst();
    Piece piece = nextMove.getPiece();

    if (nextMove.isCastlingKingside())
    {
        nextMove.castleKingside(pieces);
        movesDone.prepend(nextMove);
        return;
    }

    if (nextMove.isCastlingQueenside())
    {
        nextMove.castleQueenside(pieces);
        movesDone.prepend(nextMove);
        return;
    }

    Position previousPosition = piece.position;

    if (!pieces.contains(previousPosition))
    {
        //TODO error
        return;
    }

    if (nextMove.isCapture())
    {
        takenPieces.append(pieces.value(nextMove.getNextPosition()));
    }

    piece.position = nextMove.getNextPosition();
    pieces.remove(previousPosition);
    pieces.insert(nextMove.getNextPosition(), piece);

    movesDone.prepend(nextMove);

    return;
}

void GameManager::previousMove()
{
    if (movesDone.isEmpty())
    {
        //TODO error
        return;
    }

    Move previousMove = movesDone.takeFirst();
    Piece piece = previousMove.getPiece();

    if (previousMove.isCastlingKingside())
    {
        previousMove.undoCastleKingside(pieces);
        nextMoves.prepend(previousMove);
        return;
    }

    Position currentPosition = previousMove.getNextPosition();

    if (!pieces.contains(currentPosition))
    {
        //TODO error
        return;
    }

    piece.position = previousMove.getPreviousPosition();
    pieces.remove(currentPosition);
    pieces.insert(previousMove.getPreviousPosition(), piece);

    if (previousMove.isCapture())
    {
        previousMove.getCapturedPiece().position = currentPosition;
        pieces.insert(currentPosition, previousMove.getCapturedPiece());
    }

    nextMoves.prepend(previousMove);

    return;
}

bool GameManager::hasNextMove()
{
    return !nextMoves.isEmpty();
}

bool GameManager::hasPreviousMove()
{
    return !movesDone.isEmpty();
}
