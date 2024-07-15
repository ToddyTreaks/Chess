#ifndef PIECE_H
#define PIECE_H

#include <QString>
#include <QFile>

#include "position.h"

class MovementStrategy;

class Piece
{
public:
    Piece();
    Piece(const Piece &piece);
    Piece(bool colorIsWhite, QString pgnIdentifier, Position position);
    ~Piece();

    Position position;

    bool isWhite() const;
    QString getPgnIdentifier() const;
    QString getIconFileName() const;

    QString toString() const;

    bool matchPosition(const Position &nextPosition, Position prerequisite, const QList<Piece> &pieces) const;

    static Piece findPiece(Position position, const QList<Piece> &pieces);
    static Piece findPiece(QString pgnIdentifier, bool colorIsWhite, const QList<Piece> &pieces);
    static Piece findPiece(QString pgnIdentifier, bool colorIsWhite, const Position &nextPosition, Position prerequisite, const QList<Piece> &pieces);

    static QList<Piece> createStartingPieces();

    bool operator==(const Piece& other) const;

protected:

    bool canGoTo(const Position &targetPosition, const QList<Piece> &pieces) const;

    bool colorIsWhite;
    QString pgnIdentifier;
    QString iconFileName;

    MovementStrategy *movementStrategy;
};

#endif // PIECE_H
