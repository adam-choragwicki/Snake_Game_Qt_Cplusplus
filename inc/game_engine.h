#pragma once

#include "snake.h"
#include "food.h"
#include "speed_manager.h"

#include <QTimer>

enum class Key
{
    left,
    right,
    up,
    down,
    plus,
    minus,
    space
};

class GameEngine : public QObject
{
Q_OBJECT

signals:
    void redrawSnakeSignal();
    void dialogRestartGameSignal();

public:
    GameEngine();
    void processKeyPress(const Key& key);
    Snake& getSnake() {return snake_;}
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
