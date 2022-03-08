#include "game_window.h"

#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication application(argc, argv);
    GameWindow gameWindow;
    gameWindow.show();

    return application.exec();
}
