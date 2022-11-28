#include "game.h"

int main(int argc, char* argv[])
{
    QApplication application(argc, argv);
    Game game;

    return QApplication::exec();
}

//TODO add end game win
//TODO food should be created only on empty fields
//TODO add points
//TODO grow mechanism has some bug on tail
