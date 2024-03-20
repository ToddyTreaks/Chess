#ifndef POSITION_H
#define POSITION_H


class Position
{
public:
    Position();
    Position(int row, int column);

    int row;
    int column;

    bool operator<(const Position& other) const;

};

#endif // POSITION_H
