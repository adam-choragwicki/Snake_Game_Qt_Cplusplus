#include "game_manager.h"
#include "model/model.h"
#include "game_loop.h"
#include "spdlog/spdlog.h"

GameManager::GameManager(Model& model) : model_(model)
{
    gameState_ = GameState::BEFORE_FIRST_RUN;
}

void GameManager::processRestartGameRequest()
{
    spdlog::debug("Processing start or restart game request");

    prepareGameToStart();

    if(gameState_ == GameState::READY_TO_START)
    {
        startGame();
    }
    else
    {
        spdlog::debug("Game is not in READY_TO_START state. Start or restart game request rejected");
    }
}

void GameManager::prepareGameToStart()
{
    spdlog::debug("Prepare game to start");

    if(gameState_ != GameState::BEFORE_FIRST_RUN)
    {
        model_.reset();
    }

    gameState_ = GameState::READY_TO_START;
}

void GameManager::startGame()
{
    spdlog::debug("Start game");

    gameState_ = GameState::RUNNING;
    gameLoop_->start();
    model_.getScene()->invalidate();
}

void GameManager::endGame()
{
    spdlog::debug("End game");

    gameState_ = GameState::STOPPED;
    gameLoop_->stop();
    model_.getScene()->invalidate();
}
