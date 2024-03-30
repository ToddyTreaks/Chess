#include "mainwindow.h"

#include "gamemanager.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    GameManager game("D:/documents/chess/Chess/Chess/pgnTests/test2.pgn");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
