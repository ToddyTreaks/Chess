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

bool Piece::isWhite() const
{
    return colorIsWhite;
}

QString Piece::getPgnIdentifier() const
{
    return pgnIdentifier;
}

QString Piece::getIconFileName() const
{
    return iconFileName;
}

QString Piece::toString()
{
    QString pieceToString("%1, %2, %3");
    pieceToString = pieceToString.arg(pgnIdentifier);
    if (colorIsWhite)
    {
        pieceToString = pieceToString.arg("White");
    }
    else
    {
        pieceToString = pieceToString.arg("Black");
    }
    pieceToString = pieceToString.arg(position.toString());
    return pieceToString;
}

Piece Piece::findPiece(Position position, const QList<Piece> &pieces)
{
    QListIterator iterator(pieces);
    while (iterator.hasNext())
    {
        Piece piece = iterator.next();
        if (piece.position == position)
        {
            return piece;
        }
    }
    throw std::out_of_range("Piece not found !");
}

Piece Piece::findPiece(QString pgnIdentifier, bool colorIsWhite, const QList<Piece> &pieces)
{
    QListIterator iterator(pieces);
    while (iterator.hasNext())
    {
        Piece candidate = iterator.next();
        if (candidate.isWhite() == colorIsWhite && candidate.getPgnIdentifier() == pgnIdentifier)
        {
            return candidate;
        }
    }
    throw std::out_of_range("Piece not found.");
}

Piece Piece::findPiece(QString pgnIdentifier, bool colorIsWhite, const Position &nextPosition, Position prerequisite, const QList<Piece> &pieces)
{
    if (pieces.isEmpty())
    {
        throw std::out_of_range("Piece not found");
    }

    QList<Piece> candidates;
    QListIterator iterator(pieces);
    while (iterator.hasNext())
    {
        Piece actualBoardPiece = iterator.next();
        if (actualBoardPiece.isWhite() == colorIsWhite && actualBoardPiece.getPgnIdentifier() == pgnIdentifier)
        {
            candidates.append(actualBoardPiece);
        }
    }

    iterator = QListIterator(candidates);
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

bool Piece::matchPosition(const Position &nextPosition, Position prerequisite, const QList<Piece> &pieces)
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

bool Piece::canGoTo(const Position &nextPosition, const QList<Piece> &pieces)
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

bool Piece::operator==(const Piece& other) const
{
    bool sameColor = (other.isWhite() == colorIsWhite);
    bool samePosition = (other.position == position);
    bool samePieceType = (other.getPgnIdentifier() == pgnIdentifier);
    return sameColor && samePosition && samePieceType;
}
