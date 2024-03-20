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

    static Piece findPiece(QString pngIdentifier, QString color, Position nextPosition, Position prerequisite, const QList<Piece> &pieces);

    QString getName();
    QString getColor();
    QString getPngIdentifier();
    QString toString();

private:
    bool canGoTo(Position targetPosition, const QList<Piece> &pieces);

    QString name;
    QString color;
    QString pngIdentifier;
    Position position;
    QIcon icon;
};

#endif // PIECE_H
