#include "piece.h"

#include <QMap>
#include <QDebug>

#include "board.h"

Piece::Piece() {}

Piece::Piece(QString color, QString pgnIdentifier, Position position)
    : color(color), pgnIdentifier(pgnIdentifier), position(position), icon()
{
    //TODO : change this
    QString iconFileName("img/pawn_icon.png");
    icon = QIcon(iconFileName);
}

QString Piece::getColor()
{
    return color;
}

QString Piece::getPgnIdentifier()
{
    return pgnIdentifier;
}

QString Piece::toString()
{
    return QString("%1, %2").arg(pgnIdentifier).arg(position.toString());
}

Piece* Piece::findPiece(QString pngIdentifier, QString color, Position nextPosition, Position prerequisite, const QMap<Position, Piece *> &pieces)
{
    if (pieces.isEmpty())
    {
        //TODO error
        return NULL;
    }

    QList<Piece*> candidates;
    for (auto iterator = pieces.keyValueBegin(); iterator != pieces.keyValueEnd(); ++iterator)
    {
        Piece* actualBoardPiece = iterator->second;

        if (actualBoardPiece->getColor() == color && actualBoardPiece->getPgnIdentifier() == pngIdentifier)
        {
            candidates.append(actualBoardPiece);
        }

    }

    QListIterator iterator(candidates);
    while (iterator.hasNext())
    {
        Piece* candidate = iterator.next();
        qDebug() << nextPosition.toString() << prerequisite.toString();
        qDebug() << candidate->toString();
        qDebug() << candidate->matchPosition(nextPosition, prerequisite, pieces);
        if (candidate->matchPosition(nextPosition, prerequisite, pieces))
        {
            return candidate;
        }
    }
    //TODO error
    return NULL;

}

bool Piece::matchPosition(Position nextPosition, Position prerequisite, const QMap<Position, Piece*> &pieces)
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
