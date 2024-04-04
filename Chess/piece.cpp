#include "piece.h"
#include "movement/movementstrategy.h"

#include <QMap>
#include <QDebug>

#include "movement/bishopmovementstrategy.h"
#include "movement/kingmovementstrategy.h"
#include "movement/knightmovementstrategy.h"
#include "movement/pawnmovementstrategy.h"
#include "movement/queenmovementstrategy.h"
#include "movement/rookmovementstrategy.h"

Piece::Piece() {}

Piece::Piece(const Piece &piece)
    : Piece(piece.colorIsWhite, piece.pgnIdentifier, piece.position)
{}

Piece::Piece(bool colorIsWhite, QString pgnIdentifier, Position position)
    : colorIsWhite(colorIsWhite), pgnIdentifier(pgnIdentifier), position(position)
{
    iconFileName = QString(":/images/img/%1_%2.png");
    if (colorIsWhite)
    {
        iconFileName = iconFileName.arg("White");
    }
    else
    {
        iconFileName = iconFileName.arg("Black");
    }
    iconFileName = iconFileName.arg(pgnIdentifier);

    if (pgnIdentifier == "B")
    {
        movementStrategy = new BishopMovementStrategy();
    }
    else if (pgnIdentifier == "K")
    {
        movementStrategy = new KingMovementStrategy();
    }
    else if (pgnIdentifier == "N")
    {
        movementStrategy = new KnightMovementStrategy();
    }
    else if (pgnIdentifier == "Q")
    {
        movementStrategy = new QueenMovementStrategy();
    }
    else if (pgnIdentifier == "R")
    {
        movementStrategy = new RookMovementStrategy();
    }
    else
    {
        movementStrategy = new PawnMovementStrategy();
    }
}

Piece::~Piece() {}

bool Piece::isWhite()
{
    return colorIsWhite;
}

QString Piece::getPgnIdentifier()
{
    return pgnIdentifier;
}

QString Piece::getIconFileName()
{
    return iconFileName;
}

QString Piece::toString()
{
    return QString("%1, %2").arg(pgnIdentifier).arg(position.toString());
}

Piece Piece::findPiece(QString pgnIdentifier, bool colorIsWhite, const QMap<Position, Piece> &pieces)
{
    for (auto iterator = pieces.keyValueBegin(); iterator != pieces.keyValueEnd(); ++iterator)
    {
        Piece candidate = iterator->second;

        if (candidate.isWhite() == colorIsWhite && candidate.getPgnIdentifier() == pgnIdentifier)
        {
           return candidate;
        }
    }

    throw std::out_of_range("Piece not found");
}

Piece Piece::findPiece(QString pgnIdentifier, bool colorIsWhite, const Position &nextPosition, Position prerequisite, const QMap<Position, Piece> &pieces)
{
    if (pieces.isEmpty())
    {
        throw std::out_of_range("Piece not found");
    }

    QList<Piece> candidates;
    for (auto iterator = pieces.keyValueBegin(); iterator != pieces.keyValueEnd(); ++iterator)
    {
        Piece actualBoardPiece = iterator->second;
        if (actualBoardPiece.isWhite() == colorIsWhite && actualBoardPiece.getPgnIdentifier() == pgnIdentifier)
        {
            candidates.append(actualBoardPiece);
        }

    }

    QListIterator iterator(candidates);
    while (iterator.hasNext())
    {
        Piece candidate = iterator.next();
        if (candidate.matchPosition(nextPosition, prerequisite, pieces))
        {
            return candidate;
        }
    }

    throw std::out_of_range("Piece not found");

}

bool Piece::matchPosition(const Position &nextPosition, Position prerequisite, const QMap<Position, Piece> &pieces)
{
    if (prerequisite.row != 0 && prerequisite.row != position.row)
    {
        return false;
    }

    if (prerequisite.column != 0 && prerequisite.column != position.column)
    {
        return false;
    }

    return canGoTo(nextPosition, pieces);
}

bool Piece::canGoTo(const Position &nextPosition, const QMap<Position, Piece> &pieces)
{
    if (nextPosition == position)
    {
        return false;
    }

    if (!nextPosition.isEmpty(colorIsWhite, pieces))
    {
        return false;
    }
    return movementStrategy->canGoTo(position, nextPosition, pieces);
}
