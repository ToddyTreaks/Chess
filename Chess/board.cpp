#include "board.h"

Board::Board()
    : pieces(), takenPieces()
{
    //TODO add all pieces
    Position e1(5, 1);
    Piece whiteKing("whiteKing", "white", e1);

    Position e8(5, 8);
    Piece blackKing("blackKing", "black", e1);

    pieces.append(whiteKing);
    pieces.append(blackKing);
}
