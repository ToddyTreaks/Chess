#include "queen.h"

#include "bishop.h"
#include "rook.h"

#include <QDebug>

Queen::Queen() {}

Queen::Queen(QString color, Position position)
    : Piece(color, "Q", position)
{}

bool Queen::canGoTo(const Position &targetPosition, const QMap<Position, Piece*> &pieces)
{
    Bishop dummyBishop(*this);
    Rook dummyRook(*this);

    return dummyBishop.canGoTo(targetPosition, pieces) || dummyRook.canGoTo(targetPosition, pieces);
    return true;
}
