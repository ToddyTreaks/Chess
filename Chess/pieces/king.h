#ifndef KING_H
#define KING_H

#include "../piece.h"

class King : public Piece
{
public:
    King();
    King(QString color, Position position);

    void castleKingside(QMap<Position, Piece*> &pieces);
    void castleQueenside(QMap<Position, Piece*> &pieces);
    void undoCastleKingside(QMap<Position, Piece*> &pieces);
    void undoCastleQueenside(QMap<Position, Piece*> &pieces);

    bool canGoTo(const Position &targetPosition, const QMap<Position, Piece*> &pieces);
    bool canCastleKingside(const QMap<Position, Piece*> &pieces);
    bool canCastleQueenside(const QMap<Position, Piece*> &pieces);
};

#endif // KING_H
