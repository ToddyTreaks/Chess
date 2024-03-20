#include "piece.h"

#include "board.h"

Piece::Piece() {}

Piece::Piece(QString name, QString color, Position position)
    : name(name), color(color), position(position), icon()
{
    //TODO : change this
    QString iconFileName("img/pawn_icon.png");
    icon = QIcon(iconFileName);
}

Piece Piece::findPiece(QString pngIdentifier, QString color, Position nextPosition, Position prerequisite, const QList<Piece> &pieces)
{
    QList<Piece> candidates;

    QListIterator iterator(pieces);
    while (iterator.hasNext())
    {
        Piece actualBoardPiece = iterator.next();

        if (actualBoardPiece.getColor() == color && actualBoardPiece.getPngIdentifier() == pngIdentifier)
        {
            candidates.append(actualBoardPiece);
        }

    }
    return candidates.first();

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
