#include "game_engine.h"
#include "drawer.h"

GameEngine::GameEngine()
{
    connect(&speedManager_.getGameTickTimer(), &QTimer::timeout, this, &GameEngine::gameTickSlot);
}

void GameEngine::startGame()
{
    Drawer::eraseFood(food_);
    snake_.reset();

    Drawer::redrawSnake(snake_);

    food_.generate();
    Drawer::drawFood(food_);

    speedManager_.resetSpeed();
    speedManager_.startGame();
}

void GameEngine::endGame()
{
    speedManager_.stopGame();
    emit dialogRestartGameSignal();
}

void GameEngine::checkSnakeCollisionWithFoodSquare()
{
    if(snake_.getHeadPosition() == food_.getPosition())
    {
        Drawer::eraseFood(food_);
        food_.generate();
        Drawer::drawFood(food_);
        snake_.processFoodEaten();
    }
}

void GameEngine::checkSnakeCollisionWithWall()
{
    if(snake_.getHeadPosition().x() > GameParameters::Arena::maximumColumn ||
       snake_.getHeadPosition().x() < GameParameters::Arena::minimumRowColumn ||
       snake_.getHeadPosition().y() > GameParameters::Arena::maximumRow ||
       snake_.getHeadPosition().y() < GameParameters::Arena::minimumRowColumn)
    {
        endGame();
    }
}

void GameEngine::checkSnakeCollisionWithItself()
{
    QVector<Snake::Segment> snakeSegments = snake_.getSegments();

    /*Remove head position from snake positions, so it is not taken into account here*/
    snakeSegments.removeFirst();

    QPoint headPosition = snake_.getHeadPosition();

    if(snakeSegments.contains(headPosition))
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

void GameEngine::setGameSpeedLevel()
{
    speedManager_.setGameSpeedLevel();
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

void GameEngine::gameTickSlot()
{
    snake_.move();
    snake_.setDirection(snake_.getNextDirection());

    checkSnakeCollisionWithWall();
    checkSnakeCollisionWithItself();
    checkSnakeCollisionWithFoodSquare();

    Drawer::redrawSnake(snake_);
}
