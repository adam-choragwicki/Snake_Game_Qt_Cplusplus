#include "game_loop.h"
#include "model/model.h"
#include "collision_manager.h"
#include <QTimer>
#include "spdlog/spdlog.h"

GameLoop::GameLoop(Model& model) : model_(model), arena_(model_.getArena()), snake_(model_.getSnake())
{
    gameLoopTimer_ = std::make_unique<QTimer>();
    gameLoopTimer_->setTimerType(Qt::PreciseTimer);
    gameLoopTimer_->setInterval(ConfigProd::MOVEMENT_DELAY_MS);
    connect(gameLoopTimer_.get(), &QTimer::timeout, this, &GameLoop::execute);
}

void GameLoop::start()
{
    gameLoopTimer_->start();
}

void GameLoop::stop()
{
    gameLoopTimer_->stop();
}

void GameLoop::execute()
{
    newFoodPosition = true;

    if(CollisionManager::checkSnakeCollisionWithArenaBoundary(snake_, arena_))
    {
        spdlog::debug("Hit arena boundary, head at: {}", snake_.getHeadCoordinates().toString().toStdString());
        emit endGame();
        return;
    }

    if(CollisionManager::checkSnakeCollisionWithItself(snake_))
    {
        spdlog::debug("Hit itself, head at: {}", snake_.getHeadCoordinates().toString().toStdString());
        emit endGame();
        return;
    }

    if(model_.getFoodManager().foodExists())
    {
        if(CollisionManager::checkSnakeCollisionWithFood(snake_, model_.getFoodManager().getFood()))
        {
            spdlog::debug("Hit food, head at: {}", snake_.getHeadCoordinates().toString().toStdString());
            snake_.eatFood();
            model_.getFoodManager().respawnFood();
        }
    }

    if(snake_.isSupposedToGrow())
    {
        snake_.grow();
    }

    snake_.moveForward();

    if(snake_.isNewMovementDirectionRequested())
    {
        snake_.updateMovementDirection();
    }

    if(newFoodPosition)
    {
        snake_.setNewFoodPosition(model_.getFoodManager().getFood().sceneBoundingRect().center());
        newFoodPosition = false;
    }
}
