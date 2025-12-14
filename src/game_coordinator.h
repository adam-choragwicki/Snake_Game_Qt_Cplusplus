#pragma once

#include "model.h"
#include "game_loop.h"
#include "qml_helper.h"

class GameCoordinator
{
public:
    explicit GameCoordinator(Model& model, GameLoop& gameLoop);

    void setQmlHelper(QmlHelper* qmlHelper);

    void startGameLoop();
    void stopGameLoop();

    void restartGame();

private:
    Model& model_;
    GameLoop& gameLoop_;
    QmlHelper* qmlHelper_{};
};
