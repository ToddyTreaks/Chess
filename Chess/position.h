#ifndef POSITION_H
#define POSITION_H

#include <QString>

class Piece;

class Position
{
public:

    /*
    * Constructors
    */
    Position();
    Position(int row, int column);

    /*
    * Attributes
    */
    int row;
    int column;
    /*
    * @return the position in the form of a string 
    */
    QString toString() const;
    /*
    * @param pieces: the pieces on the board
    * @raise nothing
    * @return true if the position is empty, false otherwise
    */
    bool isEmpty(const QMap<Position, Piece> &pieces) const;
    /*
    * @param color: the color of the piece
    * @param QMap<Position, Piece>: a map of the pieces on the board that use the position as key
    * @raise nothing
    * @return true if the position is empty, false otherwise
    */
    bool isEmpty(QString color, const QMap<Position, Piece> &pieces) const;

    /*
    * @param position: the position to compare
    */
    bool operator<(const Position& other) const;
    /*
    * @param position: the position to compare
    */    
    bool operator==(const Position& other) const;
    /*
    * @param position: the position to compare
    */  
    bool operator!=(const Position& other) const;

};

#endif // POSITION_H
