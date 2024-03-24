#ifndef PIECE_H
#define PIECE_H

#include <QString>
#include <QIcon>

#include "position.h"
#include <QMap>

class Board;

class Piece
{
public:
    Piece();
    Piece(QString color, QString pgnIdentifier, Position position);

    Position position;

    QString getColor();
    QString getPgnIdentifier();
    QString toString();

    bool matchPosition(Position nextPosition, Position prerequisite, const QMap<Position, Piece> &pieces);

    static Piece findPiece(QString pngIdentifier, QString color, Position nextPosition, Position prerequisite, const QMap<Position, Piece> &pieces);

private:

    virtual bool canGoTo(Position targetPosition, const QMap<Position, Piece> &pieces);

    QString color;
    QString pgnIdentifier;
    QIcon icon;
};

#endif // PIECE_H
