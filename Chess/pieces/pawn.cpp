#include "pawn.h"

Pawn::Pawn() {}

Pawn::Pawn(QString color, Position position)
    : Piece(color, "", position)
{}

bool Pawn::canGoTo(const Position &targetPosition, const QMap<Position, Piece*> &pieces) {

    int x_target = std::abs(targetPosition.column - position.column);
    int y_target = std::abs(targetPosition.row - position.row);

    if (y_target == 1)
        // cas de la prise
        if (x_target == 1 && pieces.contains(targetPosition)){
            return true;
        }
        // cas ou il n'y a rien devant
        if (x_target == 0 && !(pieces.contains(targetPosition))){
            return true;
        }
    return false;
}
