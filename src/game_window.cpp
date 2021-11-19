#include "game_window.h"
#include "ui_game_window.h"
#include "drawer.h"

GameWindow::GameWindow(QWidget* parent) : QMainWindow(parent), ui_(new Ui::GameWindow)
{
    ui_->setupUi(this);

    setWindowTitle("Snake");
    setFocus(Qt::ActiveWindowFocusReason);

    initializeGameplayAreaScene();

    Drawer::setScene(&scene_);

    Drawer::drawGameArena();

    food_.generateAndPlace();

    Drawer::drawSnake(snake_.getPositions(), snake_.getSnakeSquaresGraphicalRectItems());

    connect(&gameTickTimer_, &QTimer::timeout, this, &GameWindow::gameTick);

    startGame();
}

GameWindow::~GameWindow()
{
    delete ui_;
}

void GameWindow::initializeGameplayAreaScene()
{
    ui_->graphicsView->setScene(&scene_);
    scene_.setBackgroundBrush(QBrush(Qt::black));

    const int sceneWidth = gameArenaParameters::COLUMNS_COUNT * gameArenaParameters::SQUARE_SIZE + 2 * gameArenaParameters::WALL_THICKNESS;
    const int sceneHeight = gameArenaParameters::ROWS_COUNT * gameArenaParameters::SQUARE_SIZE + 2 * gameArenaParameters::WALL_THICKNESS;

    scene_.setSceneRect(0, 0, sceneWidth, sceneHeight);
}

void GameWindow::startGame()
{
    snake_.reset();
    setGameSpeedLevel(ui_->slider_Speed->value());
    gameTickTimer_.start();
}

void GameWindow::keyPressEvent(QKeyEvent* event)
{
    Snake::Direction currentDirection = snake_.getDirection();

    int sliderValue = ui_->slider_Speed->value();

    switch(event->key())
    {
    case Qt::Key_A:
    case Qt::Key_Left:
        if(currentDirection != Snake::Direction::right)
        {
            snake_.setNextDirection(Snake::Direction::left);
        }
        break;

    case Qt::Key_W:
    case Qt::Key_Up:
        if(currentDirection != Snake::Direction::down)
        {
            snake_.setNextDirection(Snake::Direction::up);
        }
        break;

    case Qt::Key_S:
    case Qt::Key_Down:
        if(currentDirection != Snake::Direction::up)
        {
            snake_.setNextDirection(Snake::Direction::down);
        }
        break;

    case Qt::Key_D:
    case Qt::Key_Right:
        if(currentDirection != Snake::Direction::left)
        {
            snake_.setNextDirection(Snake::Direction::right);
        }
        break;

    case Qt::Key_Plus:
        //Subtracting means increasing speed
        ui_->slider_Speed->setValue(sliderValue - 1);
        break;

    case Qt::Key_Minus:
        //Adding means decreasing speed
        ui_->slider_Speed->setValue(sliderValue + 1);
        break;

    case Qt::Key_Space:
        activateSpeedBoost();
        break;

    default:
        qDebug() << "Wrong key pressed";
    }
}

void GameWindow::keyReleaseEvent(QKeyEvent* event)
{
    switch(event->key())
    {
    case Qt::Key_Space:
        dectivateSpeedBoost();
        break;
    }
}

void GameWindow::checkSnakeCollisionWithFoodSquare()
{
    if(snake_.getHeadPosition() == food_.getPosition())
    {
        Drawer::eraseFood(food_.getFoodSquareGraphicalRectItem());
        food_.generateAndPlace();
        snake_.grow();
    }
}

void GameWindow::checkSnakeCollisionWithWall()
{
    /*Check if snake hit a wall*/
    if(snake_.getHeadPosition().x() > gameArenaParameters::MAXIMUM_COLUMN ||
            snake_.getHeadPosition().x() < gameArenaParameters::MINIMUM_ROW_COLUMN ||
            snake_.getHeadPosition().y() > gameArenaParameters::MAXIMUM_ROW ||
            snake_.getHeadPosition().y() < gameArenaParameters::MINIMUM_ROW_COLUMN)
    {
        gameTickTimer_.stop();

        dialogRestartGame();
    }
}

void GameWindow::dialogRestartGame()
{
    int answer = QMessageBox::question(this,
                                       "Game over",
                                       "Restart?",
                                       QMessageBox::StandardButton::Ok,
                                       QMessageBox::StandardButton::Cancel);

    if(answer == QMessageBox::Ok)
    {
        startGame();
    }
    else
    {
        exit(0);
    }
}

void GameWindow::checkSnakeCollisionWithItself()
{
    /*Check if snake hit itself*/
    QVector<QPoint> snakePositions = snake_.getPositions();

    /*Remove head position from snake positions so it is not taken into account here*/
    snakePositions.removeFirst();

    QPoint headPosition = snake_.getHeadPosition();

    if(snakePositions.contains(headPosition))
    {
        gameTickTimer_.stop();

        dialogRestartGame();
    }
}

void GameWindow::redrawSnake()
{
    Drawer::eraseSnake(snake_.getSnakeSquaresGraphicalRectItems());
    Drawer::drawSnake(snake_.getPositions(), snake_.getSnakeSquaresGraphicalRectItems());
}

void GameWindow::gameTick()
{
    snake_.move();
    snake_.setDirection(snake_.getNextDirection());

    checkSnakeCollisionWithWall();
    checkSnakeCollisionWithItself();
    checkSnakeCollisionWithFoodSquare();

    redrawSnake();
}

void GameWindow::on_m_SpeedHorizontalSlider_valueChanged(int value)
{
    setGameSpeedLevel(value);
}

void GameWindow::setGameSpeedLevel(int speedLevel)
{
    const int TIME_OFFSET = 20;

    gameTickTimer_.setInterval(TIME_OFFSET + speedLevel * 20);
}

void GameWindow::activateSpeedBoost()
{
    const int BOOST_VALUE = 20;
    gameTickTimer_.setInterval(BOOST_VALUE);
}

void GameWindow::dectivateSpeedBoost()
{
    setGameSpeedLevel(ui_->slider_Speed->value());
}
