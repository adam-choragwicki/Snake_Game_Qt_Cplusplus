#include "game.h"
#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication application(argc, argv);
    Game game;

    return QApplication::exec();
}

//TODO add points
