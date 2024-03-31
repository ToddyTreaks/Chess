#ifndef PIECE_H
#define PIECE_H

#include <QString>
#include <QFile>

#include "position.h"
#include <QMap>

class Piece
{
public:
    Piece();
    Piece(const Piece &piece);
    Piece(QString color, QString pgnIdentifier, Position position);
    ~Piece();

    Position position;

    QString getColor();
    QString getPgnIdentifier();
    QString getIconFileName();

    QString toString();

    bool matchPosition(const Position &nextPosition, Position prerequisite, const QMap<Position, Piece*> &pieces);

    static Piece* findPiece(QString pgnIdentifier, QString color, const QMap<Position, Piece*> &pieces);
    static Piece* findPiece(QString pgnIdentifier, QString color, const Position &nextPosition, Position prerequisite, const QMap<Position, Piece*> &pieces);

protected:

    bool isTravelAllowed(const Position &targetPosition, const QMap<Position, Piece*> &pieces);
    virtual bool canGoTo(const Position &targetPosition, const QMap<Position, Piece*> &pieces) = 0;

    QString color;
    QString pgnIdentifier;
    QString iconFileName;
};

#endif // PIECE_H
