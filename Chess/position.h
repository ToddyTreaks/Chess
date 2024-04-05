#ifndef POSITION_H
#define POSITION_H

#include <QString>

class Piece;

class Position
{
public:
    Position();
    Position(int row, int column);

    int row;
    int column;

    QString toString() const;
    bool isEmpty(const QList<Piece> &pieces) const;
    bool isEmpty(bool colorIsWhite, const QList<Piece> &pieces) const;

    bool operator<(const Position& other) const;
    bool operator==(const Position& other) const;
    bool operator!=(const Position& other) const;

};

#endif // POSITION_H
