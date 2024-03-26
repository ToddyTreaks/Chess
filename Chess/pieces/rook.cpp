#include "rook.h"

#include <QDebug>

Rook::Rook() {}

Rook::Rook(const Piece &piece)
    : Piece(piece)
{}

Rook::Rook(QString color, Position position)
    : Piece(color, "R", position)
{}

bool Rook::canGoTo(const Position &targetPosition, const QMap<Position, Piece*> &pieces)
{
    qDebug() << targetPosition.toString();
    qDebug() << (this == NULL);

    int x_target = std::abs(targetPosition.column - position.column);
    int y_target = std::abs(targetPosition.row - position.row);

    if (x_target != 0 && y_target != 0)
    {
        return false;
    }

    if (x_target == y_target)
    {
        return false;
    }

    if (y_target == 0)
    {
        return noBlockingPieceOnColumn(targetPosition, pieces);
    }
    else
    {
        return noBlockingPieceOnRow(targetPosition, pieces);
    }
}

bool Rook::noBlockingPieceOnColumn(const Position &targetPosition, const QMap<Position, Piece*> &pieces)
{
    int increment = (targetPosition.column - position.column) / std::abs(targetPosition.column - position.column);
    for (int i = position.column + 1; i < targetPosition.column; i += increment)
    {
        if (!Position(i, position.row).isEmpty(pieces))
        {
            return false;
        }
    }
    return true;
}


bool Rook::noBlockingPieceOnRow(const Position &targetPosition, const QMap<Position, Piece*> &pieces)
{
    int increment = (targetPosition.row - position.row) / std::abs(targetPosition.row - position.row);
    for (int i = position.row + 1; i < targetPosition.row; i += increment)
    {
        if (!Position(position.column, i).isEmpty(pieces))
        {
            return false;
        }
    }
    return true;
}


