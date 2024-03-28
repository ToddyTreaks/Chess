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

bool Position::isEmpty(const QMap<Position, Piece*> &pieces) const
{
    return !pieces.contains(*this);
}

bool Position::isEmpty(QString color, const QMap<Position, Piece*> &pieces) const
{
    if (!pieces.contains(*this))
    {
        return true;
    }

    if (pieces.value(*this) == NULL)
    {
        return true;
    }
    return !(pieces.value(*this)->getColor() == color);
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
