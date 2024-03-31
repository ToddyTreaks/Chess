#include "boarddrawer.h"

#include <QDebug>
#include <QGraphicsPixmapItem>

BoardDrawer::BoardDrawer()
    : lightBrush(QColor(235, 236, 208)),
    darkBrush(QColor(53, 124, 194)),
    lightPen(QColor(235, 236, 208)),
    darkPen(QColor(53, 124, 194))
{}

void BoardDrawer::drawSquares(QGraphicsScene* scene)
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

void BoardDrawer::drawPieces(QGraphicsScene* scene, const QMap<Position, Piece> &pieces)
{
    scene->clear();
    drawSquares(scene);
    for (auto iterator = pieces.keyValueBegin(); iterator != pieces.keyValueEnd(); ++iterator)
    {
        Piece piece = iterator->second;
        drawPiece(piece, scene);
    }
}

void BoardDrawer::drawPiece(Piece piece, QGraphicsScene* scene)
{
    QPixmap icon(piece.getIconFileName());
    icon = icon.scaled(SQUARE_SIZE, SQUARE_SIZE, Qt::KeepAspectRatio);    
    QGraphicsPixmapItem* iconItem = scene->addPixmap(icon);

    int x = getxFromPosition(piece.position);
    int y = getyFromPosition(piece.position);
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
