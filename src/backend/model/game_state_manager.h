#pragma once

#include "game_speed_manager.h"

class GameStateManager
{
    enum class State
    {
        STOPPED, PAUSED, RUNNING
    } state_;

public:
    explicit GameStateManager(GameSpeedManager& gameSpeedManager, QTimer& gameTickTimer);
    void startGame();
    void endGame();
    bool isRunning();
    void togglePause();

private:
    GameSpeedManager& gameSpeedManager_;
};
