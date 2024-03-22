#include "piece.h"

#include <QMap>

#include "board.h"

Piece::Piece() {}

Piece::Piece(QString name, QString color, Position position)
    : name(name), color(color), position(position), icon()
{
    //TODO : change this
    QString iconFileName("img/pawn_icon.png");
    icon = QIcon(iconFileName);
}

Piece Piece::findPiece(QString pngIdentifier, QString color, Position nextPosition, Position prerequisite, const QMap<Position, Piece> &pieces)
{
    if (pieces.isEmpty())
    {
        //TODO error
        Piece piece;
        return piece;
    }


    QList<Piece> candidates;
    for (auto iterator = pieces.keyValueBegin(); iterator != pieces.keyValueEnd(); ++iterator)
    {
        Piece actualBoardPiece = iterator->second;

        if (actualBoardPiece.getColor() == color && actualBoardPiece.getPngIdentifier() == pngIdentifier)
        {
            candidates.append(actualBoardPiece);
        }

    }
    Piece piece;
    return piece;

}

QString Piece::getName()
{
    return name;
}

QString Piece::getColor()
{
    return color;
}

QString Piece::getPngIdentifier()
{
    return pngIdentifier;
}

bool Piece::canGoTo(Position targetPosition, const QMap<Position, Piece> &pieces)
{
    return true;
}
