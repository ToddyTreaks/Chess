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
    pieces.append(Piece(true, "K", Position(1, 5)));
    pieces.append(Piece(true, "Q", Position(1, 4)));
    pieces.append(Piece(true, "B", Position(1, 3)));
    pieces.append(Piece(true, "B", Position(1, 6)));
    pieces.append(Piece(true, "N", Position(1, 2)));
    pieces.append(Piece(true, "N", Position(1, 7)));
    pieces.append(Piece(true, "R", Position(1, 1)));
    pieces.append(Piece(true, "R", Position(1, 8)));

    for (int i=0; i<8; i++)
    {
        pieces.append(Piece(true, "", Position(2, i+1)));
    }

    pieces.append(Piece(false, "K", Position(8, 5)));
    pieces.append(Piece(false, "Q", Position(8, 4)));
    pieces.append(Piece(false, "B", Position(8, 3)));
    pieces.append(Piece(false, "B", Position(8, 6)));
    pieces.append(Piece(false, "N", Position(8, 2)));
    pieces.append(Piece(false, "N", Position(8, 7)));
    pieces.append(Piece(false, "R", Position(8, 1)));
    pieces.append(Piece(false, "R", Position(8, 8)));

    for (int i=0; i<8; i++)
    {
        pieces.append(Piece(false, "", Position(7, i+1)));
    }
}

void GameManager::parsePgn(QString fileContent)
{
    fileContent.replace('\n', ' ');
    QStringList pgnInstructions;
    pgnInstructions = fileContent.split(' ');

    bool whiteToPlay = true;

    QListIterator iterator(pgnInstructions);
    while (iterator.hasNext())
    {
        QString pgnInstruction = iterator.next();

        qDebug() << "------------new instruction -----------------" << pgnInstruction;

        if (!isEndingIndication(pgnInstruction) && !isMoveNumber(pgnInstruction))
        {
            instanciateMoves(pgnInstruction, whiteToPlay);
            whiteToPlay = !whiteToPlay;
        }

        qDebug() << "--- board ---" << pgnInstruction;

        QListIterator printIterator(pieces);
        while (printIterator.hasNext())
        {
            Piece piece = printIterator.next();
            qDebug() << piece.toString();
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

void GameManager::instanciateMoves(QString pgnInstruction, bool whiteToPlay)
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

bool GameManager::isPromotion(QString pgnInstruction)
{
    return pgnInstruction.contains('=');
}

QString GameManager::getPiecePromotedToPgnIdentifier(QString pgnInstruction)
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

const QList<Piece> GameManager::getPieces()
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
        qDebug() << "here kingside";
        nextMove.castleKingside(pieces);
        movesDone.prepend(nextMove);
        return;
    }

    if (nextMove.isCastlingQueenside())
    {
        qDebug() << "here queenside";
        nextMove.castleQueenside(pieces);
        movesDone.prepend(nextMove);
        return;
    }

    if (nextMove.isCapture())
    {
        pieces.removeAll(nextMove.getCapturedPiece());
        takenPieces.append(nextMove.getCapturedPiece());
    }

    pieces.removeAll(piece);
    piece.position = nextMove.getNextPosition();

    if (nextMove.isPromotion())
    {
        piece = nextMove.getPiecePromotedTo();
    }

    pieces.append(piece);

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

    if (previousMove.isCastlingQueenside())
    {
        previousMove.undoCastleQueenside(pieces);
        nextMoves.prepend(previousMove);
        return;
    }

    if (previousMove.isPromotion())
    {
        pieces.removeAll(previousMove.getPiecePromotedTo());
    }

    if (previousMove.isCapture())
    {
        pieces.append(previousMove.getCapturedPiece());
    }

    piece.position = previousMove.getNextPosition();
    pieces.removeAll(piece);

    piece.position = previousMove.getPreviousPosition();
    pieces.append(piece);

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
