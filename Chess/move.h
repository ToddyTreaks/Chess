#ifndef MOVE_H
#define MOVE_H

#include <QString>

#include "position.h"
#include "piece.h"

class Move
{
public:
    
    /*
    * Constructors
    */
    Move();
    Move(Piece piece, Position nextPosition);
    Move(Piece piece, Position previousPosition, Position nextPosition);

    /*
    * @return the attributes as a string
    */
    QString toString();
    
    /*
    * @return the piece
    */
    Piece getPiece();
    
    /*
    * @return the previous position
    */
    Position getPreviousPosition();
    
    /*
    * @return the next position
    */
    Position getNextPosition();
    
    /*
    * @return true if the move is a capture, false otherwise
    */
    bool isCapture();
    
    /*
    * @return the captured piece
    */
    Piece getCapturedPiece();
    
    /*
    * @return true if the move is a promotion, false otherwise
    */
    bool isPromotion();
    
    /*
    * @return the piece promoted to
    */
    Piece getPiecePromotedTo();

    /*
    * @return true if the move is a castling kingside, false otherwise 
    */
    bool isCastlingKingside();
    
    /*
    * @return true if the move is a castling queenside, false otherwise
    */
    bool isCastlingQueenside();
    
    /*
    * @param piece: the piece captured
    * @set the captured piece and set the capture attribute to true
    */
    void setCapturedPiece(Piece capturedPiece);
    
    /*
    * @param piecePromotedToIdentifier: the identifier of the piece promoted to
    * @set the piece promoted to and set the promotion attribute to true
    */
    void setPiecePromotedTo(QString piecePromotedToIdentifier);
    
    /*
    * @param castlingKing: the king piece that castles
    * @set the castling kingside attribute to true
    */
    void setKingsideCastlingKing(Piece castlingKing);
    
    /*
    * @param castlingKing: the king piece that castles
    * @set the castling queenside attribute to true
    */
    void setQueensideCastlingKing(Piece castlingKing);
    
    /*
    * @param QMap<Position, Piece>: the pieces on the board
    * @raise nothing
    * @return nothing
    * @note perform the move for the castle king side on the board
    */
    void castleKingside(QMap<Position, Piece> &pieces);
    
    /*
    * @param QMap<Position, Piece>: the pieces on the board
    * @raise nothing
    * @return nothing
    * @note perform the move for the castle queen side on the board
    */
    void castleQueenside(QMap<Position, Piece> &pieces);
    
    /*
    * @param QMap<Position, Piece>: the pieces on the board
    * @raise nothing
    * @return nothing
    * @note undo the move for the castle king side on the board
    */
    void undoCastleKingside(QMap<Position, Piece> &pieces);
    
    /*
    * @param QMap<Position, Piece>: the pieces on the board
    * @raise nothing
    * @return nothing
    * @note undo the move for the castle queen side on the board
    */
    void undoCastleQueenside(QMap<Position, Piece> &pieces);
    
    /*
    * @param QMap<Position, Piece>: the pieces on the board
    * @raise nothing
    * @return true if the king can castle kingside, false otherwise
    */
    bool canCastleKingside(const QMap<Position, Piece> &pieces);
    
    /*
    * @param QMap<Position, Piece>: the pieces on the board
    * @raise nothing
    * @return true if the king can castle queenside, false otherwise
    */
    bool canCastleQueenside(const QMap<Position, Piece> &pieces);

private:
    Piece piece;
    Position previousPosition;
    Position nextPosition;

    bool capture;
    Piece capturedPiece;
    bool promotion;
    Piece piecePromotedTo;
    bool castlingKingside;
    bool castlingQueenside;
};

#endif // MOVE_H
