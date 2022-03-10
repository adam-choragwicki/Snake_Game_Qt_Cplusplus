#include "game_engine.h"

GameEngine::GameEngine()
{
    connect(&speedManager_.getGameTickTimer(), &QTimer::timeout, this, &GameEngine::gameTickSlot);
}

void GameEngine::startGame()
{
    Drawer::eraseFood(food_.getFoodSquareGraphicalEllipseItem());
    snake_.reset();
    food_.generateAndPlace();
    speedManager_.resetSpeed();
    speedManager_.getGameTickTimer().start();
}

void GameEngine::endGame()
{
    speedManager_.stopGame();
    emit dialogRestartGameSignal();
}

void GameEngine::processKeyPress(const Key& key)
{
    const Direction currentDirection = snake_.getDirection();

    switch(key)
    {
        case Key::left:
            if(currentDirection != Direction::right)
            {
                snake_.setNextDirection(Direction::left);
            }
            break;
        case Key::right:
            if(currentDirection != Direction::left)
            {
                snake_.setNextDirection(Direction::right);
            }
            break;
        case Key::up:
            if(currentDirection != Direction::down)
            {
                snake_.setNextDirection(Direction::up);
            }
            break;
        case Key::down:
            if(currentDirection != Direction::up)
            {
                snake_.setNextDirection(Direction::down);
            }
            break;
        case Key::plus:
            speedManager_.processIncreaseSpeed();
            break;
        case Key::minus:
            speedManager_.processDecreaseSpeed();
            break;
        case Key::space:
            activateSpeedBoost();
            break;
    }
}

void GameEngine::checkSnakeCollisionWithFoodSquare()
{
    if(snake_.getHeadPosition() == food_.getPosition())
    {
        Drawer::eraseFood(food_.getFoodSquareGraphicalEllipseItem());
        food_.generateAndPlace();
        snake_.grow();
    }
}

void GameEngine::checkSnakeCollisionWithWall()
{
    if(snake_.getHeadPosition().x() > GameArenaParameters::maximumColumn ||
       snake_.getHeadPosition().x() < GameArenaParameters::minimumRowColumn ||
       snake_.getHeadPosition().y() > GameArenaParameters::maximumRow ||
       snake_.getHeadPosition().y() < GameArenaParameters::minimumRowColumn)
    {
        endGame();
    }
}

void GameEngine::checkSnakeCollisionWithItself()
{
    QVector<QPoint> snakePositions = snake_.getPositions();

    /*Remove head position from snake positions, so it is not taken into account here*/
    snakePositions.removeFirst();

    QPoint headPosition = snake_.getHeadPosition();

    if(snakePositions.contains(headPosition))
    {
        endGame();
    }
}

void GameEngine::activateSpeedBoost()
{
    speedManager_.activateSpeedBoost();
}

void GameEngine::deactivateSpeedBoost()
{
    speedManager_.deactivateSpeedBoost();
}

void GameEngine::gameTickSlot()
{
    snake_.move();
    snake_.setDirection(snake_.getNextDirection());

    checkSnakeCollisionWithWall();
    checkSnakeCollisionWithItself();
    checkSnakeCollisionWithFoodSquare();

    emit redrawSnakeSignal();
}

void GameEngine::setGameSpeedLevel()
{
    speedManager_.setGameSpeedLevel();
}
