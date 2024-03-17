#ifndef PIECE_H
#define PIECE_H

#include <QString>
#include <QIcon>

#include "position.h"

class Piece
{
public:
    Piece();
    Piece(QString name, QString color, Position position);

    QString toString();

private:
    QString name;
    QString color;
    Position position;
    QIcon icon;
};

#endif // PIECE_H
