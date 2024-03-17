#ifndef PIECE_H
#define PIECE_H

#include <QString>
#include <QIcon>

#include "position.h"

class Piece
{
public:
    Piece();

    QString toString();

private:
    QString name;
    QString color;
    QIcon icon;
    Position position;
};

#endif // PIECE_H
