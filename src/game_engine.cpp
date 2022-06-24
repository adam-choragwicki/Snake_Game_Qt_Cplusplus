#include "game_engine.h"
#include "drawer.h"

GameEngine::GameEngine()
{
    connect(&speedManager_.getGameTickTimer(), &QTimer::timeout, this, &GameEngine::gameTickSlot);
}

void GameEngine::startGame()
{
    snake_ = std::make_unique<Snake>();
    food_ = std::make_unique<Food>();

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
    if(snake_->getHeadCoordinates() == food_->getPosition())
    {
        food_ = std::make_unique<Food>();
        snake_->processFoodEaten();
    }
}

void GameEngine::checkSnakeCollisionWithWall()
{
    const Coordinates& headCoordinates = snake_->getHeadCoordinates();

    if((headCoordinates.x > GameParameters::Arena::maximumColumn) || (headCoordinates.x < GameParameters::Arena::minimumRowColumn) ||
       (headCoordinates.y > GameParameters::Arena::maximumRow) || (headCoordinates.y < GameParameters::Arena::minimumRowColumn))
    {
        endGame();
    }
}

void GameEngine::checkSnakeCollisionWithItself()
{
    QVector<SnakeSegment*> snakeSegments = snake_->getSegments();

    /*Remove head position from snake positions, so it is not taken into account here*/
    snakeSegments.removeFirst();

    Coordinates headPosition = snake_->getHeadCoordinates();

    for(const SnakeSegment* snakeSegment : snakeSegments)
    {
        if(headPosition == snakeSegment->getCoordinates())
        {
            endGame();
        }
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
    const Direction currentDirection = snake_->getDirection();

    switch(key)
    {
        case Key::left:
            if(currentDirection != Direction::right)
            {
                snake_->setNextDirection(Direction::left);
            }
            break;
        case Key::right:
            if(currentDirection != Direction::left)
            {
                snake_->setNextDirection(Direction::right);
            }
            break;
        case Key::up:
            if(currentDirection != Direction::down)
            {
                snake_->setNextDirection(Direction::up);
            }
            break;
        case Key::down:
            if(currentDirection != Direction::up)
            {
                snake_->setNextDirection(Direction::down);
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
    snake_->moveForward();
    snake_->setDirection(snake_->getNextDirection());

    checkSnakeCollisionWithWall();
    checkSnakeCollisionWithItself();
    checkSnakeCollisionWithFoodSquare();

    Drawer::redrawSnake(*snake_);
}
