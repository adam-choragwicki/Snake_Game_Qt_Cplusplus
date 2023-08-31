#include "game_state_manager.h"

GameStateManager::GameStateManager(GameSpeedManager& gameSpeedManager, QTimer& gameTickTimer) : gameSpeedManager_(gameSpeedManager), state_(State::STOPPED)
{}

void GameStateManager::startGame()
{
    gameSpeedManager_.startTimer();
    state_ = State::RUNNING;
}

void GameStateManager::endGame()
{
    gameSpeedManager_.stopTimer();
    gameSpeedManager_.deactivateSpeedBoost();
    state_ = State::STOPPED;
}

bool GameStateManager::isRunning()
{
    return state_ == State::RUNNING;
}

void GameStateManager::togglePause()
{
    if(state_ == State::PAUSED)
    {
        gameSpeedManager_.startTimer();
        state_ = State::RUNNING;
    }
    else if(state_ == State::RUNNING)
    {
        gameSpeedManager_.stopTimer();
        state_ = State::PAUSED;
    }
}
