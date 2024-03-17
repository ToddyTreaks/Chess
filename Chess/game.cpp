#include "game.h"

#include <QTextStream>

Game::Game() {}

Game::Game(QFile file)
{
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }

    QTextStream in(&file);
    QString fileContent = in.read(MAX_PGN_CHARACTERS);

    parsePGN(fileContent);
}

void Game::parsePGN(QString fileContent)
{
    return;
}
