#ifndef PIECE_H
#define PIECE_H

#include <QString>
#include <QFile>

#include "position.h"
#include <QMap>

class MovementStrategy;

class Piece
{
public:
    /*
    * Constructors
    */
    Piece();
    Piece(const Piece &piece);
    Piece(QString color, QString pgnIdentifier, Position position);
    /*
    * Destructor
    */
    ~Piece();

    /*
    * Attributes 
    */
    Position position;

    /*
    * @return the color of the piece
    */
    QString getColor();
    
    /*
    * @return the PGN identifier of the piece
    */
    QString getPgnIdentifier();
    
    /*
    * @return the icon file name of the piece
    */
    QString getIconFileName();

    /*
    * @return the attributes as a string
    */
    QString toString();

    /*
    * @param QString: the png identifier of the piece
    * @param QString: the color of the piece
    * @param QMap<Position, Piece>: a map of the pieces on the board that use the position as key
    * @raise nothing
    * @return the piece with the given pgn identifier and color
    */
    static Piece findPiece(QString pgnIdentifier, QString color, const QMap<Position, Piece> &pieces);
    
    /*
    * @param QString: the png identifier of the piece
    * @param QString: the color of the piece
    * @param Position: the next position of the piece
    * @param Position: the prerequisite position of the piece
    * @param QMap<Position, Piece>: a map of the pieces on the board that use the position as key
    * @raise nothing
    * @return the piece with the given pgn identifier and color
    */
    static Piece findPiece(QString pgnIdentifier, QString color, const Position &nextPosition, Position prerequisite, const QMap<Position, Piece> &pieces);

private:

    bool canGoTo(const Position &targetPosition, const QMap<Position, Piece> &pieces);
    bool matchPosition(const Position &nextPosition, Position prerequisite, const QMap<Position, Piece> &pieces);


    QString color;
    QString pgnIdentifier;
    QString iconFileName;

    MovementStrategy *movementStrategy;
};

#endif // PIECE_H
