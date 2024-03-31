#include "mainwindow.h"

#include "gamemanager.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    GameManager game("D:/documents/chess/Chess/Chess/pgnTests/test2.pgn");
    QApplication application(argc, argv);
    MainWindow window;
    window.show();
    return application.exec();
}
