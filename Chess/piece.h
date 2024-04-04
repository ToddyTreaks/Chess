#ifndef PIECE_H
#define PIECE_H

#include <QString>
#include <QFile>

#include "position.h"
#include <QMap>

class MovementStrategy;

class Piece
{
public:
    Piece();
    Piece(const Piece &piece);
    Piece(bool colorIsWhite, QString pgnIdentifier, Position position);
    ~Piece();

    Position position;

    bool isWhite();
    QString getPgnIdentifier();
    QString getIconFileName();

    QString toString();

    bool matchPosition(const Position &nextPosition, Position prerequisite, const QMap<Position, Piece> &pieces);

    static Piece findPiece(QString pgnIdentifier, bool colorIsWhite, const QMap<Position, Piece> &pieces);
    static Piece findPiece(QString pgnIdentifier, bool colorIsWhite, const Position &nextPosition, Position prerequisite, const QMap<Position, Piece> &pieces);

protected:

    bool canGoTo(const Position &targetPosition, const QMap<Position, Piece> &pieces);

    bool colorIsWhite;
    QString pgnIdentifier;
    QString iconFileName;

    MovementStrategy *movementStrategy;
};

#endif // PIECE_H
