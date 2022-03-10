#pragma once

#include "snake.h"
#include "food.h"
#include "game_speed_manager.h"
#include "common.h"

#include <QTimer>

class GameEngine : public QObject
{
Q_OBJECT

signals:
    void dialogRestartGameSignal();

public:
    GameEngine();
    void processKeyPress(const Key& key);
    void startGame();

    SpeedManager& getSpeedManager() {return speedManager_;}
    void setGameSpeedLevel();
    void activateSpeedBoost();
    void deactivateSpeedBoost();

public slots:
    void gameTickSlot();

private:
    void checkSnakeCollisionWithWall();
    void checkSnakeCollisionWithItself();
    void checkSnakeCollisionWithFoodSquare();
    void endGame();

    Snake snake_;
    Food food_;
    SpeedManager speedManager_;
};
