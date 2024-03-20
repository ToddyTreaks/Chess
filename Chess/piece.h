#ifndef PIECE_H
#define PIECE_H

#include <QString>
#include <QIcon>

#include "position.h"

class Board;

class Piece
{
public:
    Piece();
    Piece(QString name, QString color, Position position);

    static Piece findPiece(QString pngIdentifier, QString color, Position nextPosition, Position prerequisite, const QMap<Position, Piece> &pieces);

    QString getName();
    QString getColor();
    QString getPngIdentifier();
    QString toString();
    Position position;

private:
    virtual bool canGoTo(Position targetPosition, const QMap<Position, Piece> &pieces);

    QString name;
    QString color;
    QString pngIdentifier;
    QIcon icon;
};

#endif // PIECE_H
