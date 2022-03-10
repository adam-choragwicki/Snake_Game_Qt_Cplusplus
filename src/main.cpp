#include "game_window.h"

#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication application(argc, argv);

    GameEngine gameEngine;

    GameWindow gameWindow(gameEngine);
    gameWindow.show();

    return application.exec();
}
