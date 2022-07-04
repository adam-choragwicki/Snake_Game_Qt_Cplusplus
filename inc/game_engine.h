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
    explicit GameEngine(QSlider* gameSpeedSlider);
    void processKeyPress(const Key& key);
    void setGameSpeedLevel();
    void activateSpeedBoost();
    void deactivateSpeedBoost();

public slots:
    void gameTickSlot();

private:
    bool checkSnakeCollisionWithWall();
    bool checkSnakeCollisionWithItself();
    void checkSnakeCollisionWithFoodSquare();
    void startGame();
    void endGame();

    std::unique_ptr<Snake> snake_;
    std::unique_ptr<Food> food_;
    std::unique_ptr<SpeedManager> speedManager_;

    enum class GameState
    {
        gameRunning,
        gameStopped,
        gamePaused
    } gameState_ = GameState::gameStopped;

    QMetaObject::Connection timerGameTickSlotConnection;
};
