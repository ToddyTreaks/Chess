#include "bishop.h"

#include "../piece.h"
Bishop::Bishop() {}
bool Bishop::canGoTo(Position targetPosition, const QMap<Position, Piece> &pieces) {

    int x_target = std::abs(targetPosition.column - position.column);

        return true;
    }
