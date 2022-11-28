#include "controller.h"
#include "collision_manager.h"

Controller::Controller(Model* model, MainWindow* view)
{
    model_ = model;
    view_ = view;
}

void Controller::startGame()
{
    speedManager_.setSpeedLevel(speedManager_.getSpeedLevel());
    speedManager_.start();
    model_->setGameState(GameState::RUNNING);
}

void Controller::endGame()
{
    model_->setGameState(GameState::STOPPED);
    speedManager_.stop();
    speedManager_.deactivateSpeedBoost();

    emit gameEndEvent(GameResult::LOSE);
}

void Controller::processKeyPressedEvent(Key key)
{
    switch(key)
    {
        case Key::LEFT:
            model_->getSnake()->setNextDirection(Direction::LEFT);
            break;

        case Key::RIGHT:
            model_->getSnake()->setNextDirection(Direction::RIGHT);
            break;

        case Key::UP:
            model_->getSnake()->setNextDirection(Direction::UP);
            break;

        case Key::DOWN:
            model_->getSnake()->setNextDirection(Direction::DOWN);
            break;

        case Key::PLUS:
            incrementGameSpeed();
            break;

        case Key::MINUS:
            decrementGameSpeed();
            break;

        case Key::SPACE:
            speedManager_.activateSpeedBoost();
            break;
    }
}

void Controller::processSpeedBoostKeyReleasedEvent()
{
    speedManager_.deactivateSpeedBoost();
}

void Controller::subscribeToKeyEvents()
{
    connect(view_, &MainWindow::keyPressedEvent, this, &Controller::processKeyPressedEvent);
    connect(view_, &MainWindow::speedBoostKeyReleasedEvent, this, &Controller::processSpeedBoostKeyReleasedEvent);
}

void Controller::subscribeToSpeedSliderValueChangeEvent()
{
    connect(view_->getSpeedSlider(), &QSlider::valueChanged, this, &Controller::processSliderValueChanged);
}

void Controller::subscribeViewToGameEndEvent()
{
    connect(this, &Controller::gameEndEvent, view_, &MainWindow::processGameEndEvent);
}

void Controller::subscribeToGameTickTimer()
{
    connect(&speedManager_.getGameTickTimer(), &QTimer::timeout, this, &Controller::gameTickHandler);
}

void Controller::subscribeViewToSnakePositionChangedEvent()
{
    connect(model_->getSnake(), &Snake::positionChangedEvent, view_->getGameArena(), &GameArena::updateArena);
}

void Controller::processSliderValueChanged(int sliderValue)
{
    speedManager_.setSpeedLevel(sliderValue);
}

void Controller::incrementGameSpeed()
{
    speedManager_.incrementSpeed();
    view_->getSpeedSlider()->setValue(speedManager_.getSpeedLevel());
}

void Controller::decrementGameSpeed()
{
    speedManager_.decrementSpeed();
    view_->getSpeedSlider()->setValue(speedManager_.getSpeedLevel());
}

void Controller::gameTickHandler()
{
    Snake* snake = model_->getSnake();

    if(model_->getGameState() == GameState::RUNNING)
    {
        if(CollisionManager::checkSnakeCollisionWithWall(snake))
        {
            LOG(INFO) << "Hit wall, head at: " << snake->getHeadCoordinates();
            endGame();
            return;
        }

        if(CollisionManager::checkSnakeCollisionWithItself(snake))
        {
            LOG(INFO) << "Hit itself, head at: " << snake->getHeadCoordinates();
            endGame();
            return;
        }

        if(CollisionManager::checkSnakeCollisionWithFoodSquare(snake, model_->getFood()))
        {
            LOG(INFO) << "Hit food, head at: " << snake->getHeadCoordinates();
            snake->processFoodEaten();
            model_->generateFood();
        }

        snake->moveForward();
        snake->setDirection(snake->getNextDirection());
    }
}
