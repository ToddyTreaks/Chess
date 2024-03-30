#include "king.h"

King::King() {}

King::King(QString color, Position position)
    : Piece(color, "K", position)
{}

void King::castleKingside(QMap<Position, Piece *> &pieces)
{
    if (!canCastleKingside(pieces))
    {
        // TODO error
        return;
    }

    Piece* rook;
    Position rookPosition(1, 8);

    if (color == "Black")
    {
        rookPosition.row = 8;
    }
    rook = pieces.value(rookPosition);

    Position kingNextPosition(this->position.row, this->position.column + 2);
    Position rookNextPosition(rookPosition.row, rookPosition.column - 2);

    pieces.remove(this->position);
    pieces.remove(rookPosition);

    this->position = kingNextPosition;
    pieces.insert(kingNextPosition, this);
    pieces.insert(rookNextPosition, rook);

}

bool King::canGoTo(const Position &targetPosition, const QMap<Position, Piece*> &pieces) {

    int x_target = std::abs(targetPosition.column - position.column);
    int y_target = std::abs(targetPosition.row - position.row);

    if ((x_target == 1 && y_target == 1) || (x_target + y_target ==1))
    {
        return true;
    }

    return false;
}

bool King::canCastleKingside(const QMap<Position, Piece *> &pieces)
{
    // TODO
    return true;
}

bool King::canCastleQueenside(const QMap<Position, Piece *> &pieces)
{
    // TODO
    return true;
}
