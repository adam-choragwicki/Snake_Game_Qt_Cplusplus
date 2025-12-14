#include "game_loop.h"
#include "model.h"
#include "collision_manager.h"
#include <QTimer>

GameLoop::GameLoop(Model& model, const int snakeMovementIntervalMs) : model_(model), arena_(model_.getArena()), snake_(model_.getSnake())
{
    timer_ = std::make_unique<QTimer>();
    timer_->setTimerType(Qt::PreciseTimer);
    timer_->setInterval(snakeMovementIntervalMs);
    connect(timer_.get(), &QTimer::timeout, this, &GameLoop::execute);
}

void GameLoop::start()
{
    qDebug() << "Game loop start";
    timer_->start();
}

void GameLoop::stop()
{
    timer_->stop();
}

void GameLoop::execute()
{
    // qDebug() << "GameLoop::execute";

    // set the new movement direction immediately to make the snake more responsive
    if (snake_.isNewMovementDirectionRequested())
    {
        snake_.updateMovementDirection();
    }

    if (CollisionManager::checkSnakeCollisionWithArenaBoundary(snake_, arena_))
    {
        qInfo().noquote() << "Snake hit arena boundary, head at:" << snake_.getHeadCoordinates().toString().toStdString();
        emit endGame();
        return;
    }

    if (CollisionManager::checkSnakeCollisionWithItself(snake_))
    {
        qInfo().noquote() << "Snake hit itself, head at:" << snake_.getHeadCoordinates().toString().toStdString();
        emit endGame();
        return;
    }

    snake_.moveForward();

    if (snake_.isSupposedToGrow())
    {
        snake_.grow();
    }

    if (const Coordinates foodCoordinates = model_.getFoodManager().getFoodCoordinates(); CollisionManager::checkSnakeCollisionWithFood(snake_, foodCoordinates))
    {
        qInfo().noquote() << "Snake hit food, head at:" << snake_.getHeadCoordinates().toString().toStdString();
        snake_.eatFood();
        model_.getScoreManager().increaseScore();
        model_.getFoodManager().spawnFoodAtRandomCoordinates(); // respawn food immediately. FoodFactory uses current snake coordinates to avoid placing on snake.
    }
}
