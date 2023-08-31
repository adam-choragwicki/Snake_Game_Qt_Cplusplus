#include "controller.h"
#include "collision_detector.h"
#include <QCoreApplication>

Controller::Controller(Model& model, MainWindow& view) : model_(model), view_(view)
{
    connect(&model_.getGameTickTimer(), &QTimer::timeout, this, &Controller::gameTickHandler);
    connect(&view_, &MainWindow::keyPressedEvent, this, &Controller::processKeyPressedEvent);
    connect(&view_, &MainWindow::keyReleasedEvent, this, &Controller::processKeyReleasedEvent);
    connect(view_.getSpeedSlider(), &QSlider::valueChanged, this, &Controller::processSliderValueChanged);
    connect(&view_, &MainWindow::newGameRequest, this, &Controller::startGame);
    connect(&view_, &MainWindow::applicationTerminationRequest, this, &Controller::processApplicationTerminationRequest);

    view_.getSpeedSlider()->setValue(Config::Speed::DEFAULT_SPEED_LEVEL);
}

void Controller::startGame()
{
    model_.reset();
    view_.getSpeedSlider()->setValue(model_.getGameSpeedManager().getSpeedLevelInteger());
    model_.getGameStateManager().startGame();
}

void Controller::endGame()
{
    model_.getGameStateManager().endGame();
    view_.showEndGameDialog();
}

void Controller::processKeyPressedEvent(QKeyEvent* keyEvent)
{
    switch(keyEvent->key())
    {
        case Qt::Key_Left:
        case Qt::Key_A:
            model_.getSnake().setNextHeadDirection(Direction::LEFT);
            break;

        case Qt::Key_Right:
        case Qt::Key_D:
            model_.getSnake().setNextHeadDirection(Direction::RIGHT);
            break;

        case Qt::Key_Up:
        case Qt::Key_W:
            model_.getSnake().setNextHeadDirection(Direction::UP);
            break;

        case Qt::Key_Down:
        case Qt::Key_S:
            model_.getSnake().setNextHeadDirection(Direction::DOWN);
            break;

        case Qt::Key_Plus:
            incrementGameSpeed();
            break;

        case Qt::Key_Minus:
            decrementGameSpeed();
            break;

        case Config::Key::BOOST_KEY:
            model_.getGameSpeedManager().activateSpeedBoost();
            break;

        case Qt::Key_P:
            model_.getGameStateManager().togglePause();
            break;
    }
}

void Controller::processKeyReleasedEvent(QKeyEvent* keyEvent)
{
    if(keyEvent->key() == Config::Key::BOOST_KEY)
    {
        model_.getGameSpeedManager().deactivateSpeedBoost();
    }
}

void Controller::processSliderValueChanged(int sliderValue)
{
    model_.getGameSpeedManager().setSpeedLevel(sliderValue);
}

void Controller::processApplicationTerminationRequest()
{
    QCoreApplication::exit(0);
}

void Controller::incrementGameSpeed()
{
    model_.getGameSpeedManager().incrementSpeed();
    view_.getSpeedSlider()->setValue(model_.getGameSpeedManager().getSpeedLevelInteger());
}

void Controller::decrementGameSpeed()
{
    model_.getGameSpeedManager().decrementSpeed();
    view_.getSpeedSlider()->setValue(model_.getGameSpeedManager().getSpeedLevelInteger());
}

void Controller::gameTickHandler()
{
    Snake& snake = model_.getSnake();

    if(model_.getGameStateManager().isRunning())
    {
        if(CollisionDetector::checkSnakeCollisionWithWall(snake))
        {
            LOG(INFO) << "Hit wall, head at: " << snake.getHeadCoordinates();
            endGame();
            return;
        }

        if(CollisionDetector::checkSnakeCollisionWithItself(snake))
        {
            LOG(INFO) << "Hit itself, head at: " << snake.getHeadCoordinates();
            endGame();
            return;
        }

        if(model_.getFoodManager().foodExists())
        {
            if(CollisionDetector::checkSnakeCollisionWithFood(snake, model_.getFoodManager().getFood()))
            {
                LOG(INFO) << "Hit food, head at: " << snake.getHeadCoordinates();
                snake.eatFood();
                model_.getFoodManager().removeFood();
            }
        }
        else
        {
            model_.getFoodManager().createFood();
        }

        snake.moveForward();
        view_.update();
    }
}
