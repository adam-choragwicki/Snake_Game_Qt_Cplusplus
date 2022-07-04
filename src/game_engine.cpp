#include "game_engine.h"
#include "drawer.h"
#include "config.h"
#include "log_manager.h"

GameEngine::GameEngine(QSlider* gameSpeedSlider)
{
    speedManager_ = std::make_unique<SpeedManager>(gameSpeedSlider);
    timerGameTickSlotConnection = connect(&speedManager_->getGameTickTimer(), &QTimer::timeout, this, &GameEngine::gameTickSlot);

    startGame();
}

void GameEngine::startGame()
{
    gameState_ = GameState::gameRunning;

    snake_ = std::make_unique<Snake>();
    food_ = std::make_unique<Food>();

    speedManager_->startGame();
}

void GameEngine::endGame()
{
    gameState_ = GameState::gameStopped;
    speedManager_->stopGame();

    emit dialogRestartGameSignal();
}

void GameEngine::checkSnakeCollisionWithFoodSquare()
{
    if(snake_->getHeadCoordinates() == food_->getPosition())
    {
        logFile << "Hit food, head at: " << snake_->getHeadCoordinates() << std::endl;

        food_ = std::make_unique<Food>();
        snake_->processFoodEaten();
    }
}

bool GameEngine::checkSnakeCollisionWithWall()
{
    const Coordinates& headCoordinates = snake_->getHeadCoordinates();
    const Direction direction = snake_->getDirection();

    if(direction == Direction::left && headCoordinates.x_ == GameParameters::Arena::minimumRowColumn)
    {
        return true;
    }
    else if(direction == Direction::right && headCoordinates.x_ == GameParameters::Arena::maximumColumn)
    {
        return true;
    }
    else if(direction == Direction::up && headCoordinates.y_ == GameParameters::Arena::minimumRowColumn)
    {
        return true;
    }
    else if(direction == Direction::down && headCoordinates.y_ == GameParameters::Arena::maximumRow)
    {
        return true;
    }

    return false;
}

bool GameEngine::checkSnakeCollisionWithItself()
{
    const Coordinates& headCoordinates = snake_->getHeadCoordinates();
    const Direction direction = snake_->getDirection();
    const auto allSegmentsCoordinatesExceptForHead = snake_->getAllSegmentsCoordinatesExceptForHead();

    if(direction == Direction::left && allSegmentsCoordinatesExceptForHead.contains(headCoordinates + std::pair{-1, 0}))
    {
        return true;
    }
    else if(direction == Direction::right && allSegmentsCoordinatesExceptForHead.contains(headCoordinates + std::pair{+1, 0}))
    {
        return true;
    }
    else if(direction == Direction::up && allSegmentsCoordinatesExceptForHead.contains(headCoordinates + std::pair{0, -1}))
    {
        return true;
    }
    else if(direction == Direction::down && allSegmentsCoordinatesExceptForHead.contains(headCoordinates + std::pair{0, +1}))
    {
        return true;
    }

    return false;
}

void GameEngine::activateSpeedBoost()
{
    speedManager_->activateSpeedBoost();
}

void GameEngine::deactivateSpeedBoost()
{
    speedManager_->deactivateSpeedBoost();
}

void GameEngine::setGameSpeedLevel()
{
    speedManager_->setGameSpeedLevel();
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
            speedManager_->processIncreaseSpeed();
            break;
        case Key::minus:
            speedManager_->processDecreaseSpeed();
            break;
        case Key::space:
            activateSpeedBoost();
            break;
    }
}

void GameEngine::gameTickSlot()
{
    if(gameState_ == GameState::gameRunning)
    {
        if(bool hitWall; (hitWall = checkSnakeCollisionWithWall()) || checkSnakeCollisionWithItself())
        {
            if(hitWall)
            {
                logFile << "Hit wall, head at: " << snake_->getHeadCoordinates() << std::endl;
            }
            else
            {
                logFile << "Hit itself, head at: " << snake_->getHeadCoordinates() << std::endl;
            }

            endGame();
            return;
        }

        checkSnakeCollisionWithFoodSquare();

        snake_->moveForward();
        snake_->setDirection(snake_->getNextDirection());
    }

    Drawer::updateScene();
}
