#include "gamemanager.h"

#include <QTextStream>

GameManager::GameManager() {}

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
}

void GameManager::parsePgn(QString fileLine)
{
    QStringList pgnInstructions;
    pgnInstructions = fileLine.split(" ");

    QListIterator iterator(pgnInstructions);

    while (iterator.hasNext())
    {
        QString pgnInstruction = iterator.next();

        if (!isEndingIndication(pgnInstruction) && !isMoveNumber(pgnInstruction))
        {
            instanciateNewMove(pgnInstruction);
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

void GameManager::instanciateNewMove(QString pgnInstruction)
{
    QString firstLetter;
    firstLetter = pgnInstruction.first(1);

    if (firstLetter == "O")
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

    QString restOfInstruction = pgnInstruction.sliced(1);
    Position prerequisite = getPrerequisite(restOfInstruction);
    Position nextPosition = getNextPosition(restOfInstruction);
    if (firstLetter == "K")
    {
        return;
    }

    return;

}

Position GameManager::getPrerequisite(QString pgnInstruction)
{
    Position position(0, 0);
    if (pgnInstruction.size() < 2)
    {
        // TODO error
        return position;
    }
    QChar firstLetter, secondLetter, thirdLetter;
    firstLetter = pgnInstruction.at(0);
    secondLetter = pgnInstruction.at(1);

    if (firstLetter.isLetter() && firstLetter != 'x' && secondLetter == 'x' || secondLetter.isNumber())
    {
        position.column = firstLetter.digitValue() - QChar('a').digitValue();
        return position;
    }

    if (firstLetter.isNumber() && secondLetter.isLetter())
    {
        position.row = firstLetter.digitValue() - QChar('1').digitValue();
        return position;
    }

    if (pgnInstruction.size() < 3)
    {
        return position;
    }

    secondLetter = pgnInstruction.at(2);
    if (firstLetter.isLetter() && secondLetter.isNumber() && secondLetter.isLetter())
    {
        position.column = firstLetter.digitValue() - QChar('a').digitValue();
        position.row = firstLetter.digitValue() - QChar('1').digitValue();
        return position;
    }

    // TODO error
    return position;
}

Position GameManager::getNextPosition(QString pgnInstruction)
{
    Position position(0, 0);
    while (pgnInstruction.size() > 2 || !pgnInstruction.back().isNumber())
    {
        pgnInstruction.removeLast();
    }

    if (pgnInstruction.size() == 0)
    {
        //TODO error
        return position;
    }

    position.row =  pgnInstruction.back().digitValue() - QChar('1').digitValue();
    pgnInstruction.removeLast();
    position.column = pgnInstruction.back().digitValue() - QChar('a').digitValue();
    return position;
}


