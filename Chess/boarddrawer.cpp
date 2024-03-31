#include "boarddrawer.h"

#include <QDebug>
#include <QGraphicsPixmapItem>

BoardDrawer::BoardDrawer()
    : lightBrush(Qt::yellow), darkBrush(Qt::black), lightPen(Qt::yellow), darkPen(Qt::black)
{}

void BoardDrawer::initializeBoard(QGraphicsScene* scene)
{
    for (int x=0; x<8; x++)
    {
        for (int y=0; y<8; y++)
        {
            if ((x+y) % 2 == 0)
            {
                scene->addRect(x*SQUARE_SIZE, y*SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, darkPen, darkBrush);
            }
            else
            {
                scene->addRect(x*SQUARE_SIZE, y*SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, lightPen, lightBrush);
            }
        }
    }
}

void BoardDrawer::drawBoard(QGraphicsScene* scene)
{
    return;
}

void BoardDrawer::drawPiece(Piece* piece, QGraphicsScene* scene)
{
    QPixmap icon(":/images/img/pawn_icon.png");
    QGraphicsPixmapItem* iconItem = scene->addPixmap(icon);
    int x = getxFromPosition(piece->position);
    int y = getyFromPosition(piece->position);
    iconItem->setPos(x*SQUARE_SIZE, y*SQUARE_SIZE);
}

int BoardDrawer::getxFromPosition(Position position)
{
    return position.column - 1;
}

int BoardDrawer::getyFromPosition(Position position)
{
    return position.row - 1;
}
