#ifndef POSITION_H
#define POSITION_H

#include <QString>

class Position
{
public:
    Position();
    Position(int row, int column);

    int row;
    int column;

    QString toString();

    bool operator<(const Position& other) const;

};

#endif // POSITION_H
