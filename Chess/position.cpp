#include "position.h"

Position::Position() {}

Position::Position(int row, int column)
    : row(row),
    column(column)
{}

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

QString Position::toString()
{
    QChar columnNumber = QString::number(column).front();
    int columnLetterUnicode = QChar('a').unicode() + columnNumber.unicode() - QChar('1').unicode();
    QChar columnLetter = QChar(columnLetterUnicode);
    return QString("%1%2").arg(columnLetter).arg(row);
}
