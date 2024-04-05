#include "position.h"
#include "piece.h"

#include <QDebug>

Position::Position() {}

Position::Position(int row, int column)
    : row(row),
    column(column)
{}

QString Position::toString() const
{
    QChar columnNumber = QString::number(column).front();
    int columnLetterUnicode = QChar('a').unicode() + columnNumber.unicode() - QChar('1').unicode();
    QChar columnLetter = QChar(columnLetterUnicode);
    return QString("%1%2").arg(columnLetter).arg(row);
}

bool Position::isEmpty(const QList<Piece> &pieces) const
{
    QListIterator iterator(pieces);
    while(iterator.hasNext())
    {
        Piece piece = iterator.next();
        if (piece.position == *this)
        {
            return false;
        }
    }
    return true;
}

bool Position::isEmpty(bool colorIsWhite, const QList<Piece> &pieces) const
{
    QListIterator iterator(pieces);
    while(iterator.hasNext())
    {
        Piece piece = iterator.next();
        if (piece.position == *this)
        {
            return (piece.isWhite() != colorIsWhite);
        }
    }
    return true;
}

bool Position::operator<(const Position& other) const
{
    // Compare rows first
    if (row < other.row)
        return true;
    else if (row > other.row)
        return false;
    else
        // If rows are equal, compare columns
        return column < other.column;
}

bool Position::operator==(const Position& other) const
{
    return row == other.row && column == other.column;
}

bool Position::operator!=(const Position& other) const
{
    return !(*this==other);
}
