#include "piece.h"

Piece::Piece() {}

Piece::Piece(QString name, QString color, Position position)
    : name(name), color(color), position(position), icon()
{
    //TODO : change this
    QString iconFileName("img/pawn_icon.png");
    icon = QIcon(iconFileName);
}
