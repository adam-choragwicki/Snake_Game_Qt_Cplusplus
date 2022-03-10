#include "game_window.h"
#include "ui_game_window.h"
#include "drawer.h"

GameWindow::GameWindow(GameEngine& gameEngine, QWidget* parent) :
        QMainWindow(parent),
        ui_(new Ui::GameWindow),
        gameEngine_(gameEngine)
{
    ui_->setupUi(this);

    setWindowTitle("Snake");
    setFocus(Qt::ActiveWindowFocusReason);

    initializeGameplayAreaScene();

    Drawer::setScene(&scene_);

    Drawer::drawGameArena();

    gameEngine_.getSpeedManager().connectSlider(*ui_->slider_Speed);

    Drawer::drawSnake(gameEngine_.getSnake().getPositions(), gameEngine.getSnake().getSnakeSquaresGraphicalRectItems());

    connect(ui_->slider_Speed, &QSlider::valueChanged, this, &GameWindow::speedSliderValueChangedSlot);
    connect(&gameEngine_, &GameEngine::redrawSnakeSignal, this, &GameWindow::redrawSnakeSlot);
    connect(&gameEngine_, &GameEngine::dialogRestartGameSignal, this, &GameWindow::dialogRestartGameSlot);

    gameEngine_.startGame();
}

GameWindow::~GameWindow()
{
    delete ui_;
}

void GameWindow::initializeGameplayAreaScene()
{
    ui_->graphicsView->setScene(&scene_);
    scene_.setBackgroundBrush(QBrush(Qt::black));

    const int sceneWidth = GameArenaParameters::columnCount * GameArenaParameters::snakeSegmentSize + 2 * GameArenaParameters::wallThickness;
    const int sceneHeight = GameArenaParameters::rowsCount * GameArenaParameters::snakeSegmentSize + 2 * GameArenaParameters::wallThickness;

    scene_.setSceneRect(0, 0, sceneWidth, sceneHeight);
}

void GameWindow::keyPressEvent(QKeyEvent* event)
{
    switch(event->key())
    {
        case Qt::Key_Left:
        case Qt::Key_A:
            gameEngine_.processKeyPress(Key::left);
            break;

        case Qt::Key_Right:
        case Qt::Key_D:
            gameEngine_.processKeyPress(Key::right);
            break;

        case Qt::Key_Up:
        case Qt::Key_W:
            gameEngine_.processKeyPress(Key::up);
            break;

        case Qt::Key_Down:
        case Qt::Key_S:
            gameEngine_.processKeyPress(Key::down);
            break;

        case Qt::Key_Plus:
            gameEngine_.processKeyPress(Key::plus);
            break;

        case Qt::Key_Minus:
            gameEngine_.processKeyPress(Key::minus);
            break;

        case Qt::Key_Space:
            gameEngine_.processKeyPress(Key::space);
            break;
    }
}

void GameWindow::keyReleaseEvent(QKeyEvent* event)
{
    switch(event->key())
    {
        case Qt::Key_Space:
            gameEngine_.deactivateSpeedBoost();
            break;
    }
}

void GameWindow::dialogRestartGameSlot()
{
    int answer = QMessageBox::question(this,
                                       "Game over",
                                       "Restart?",
                                       QMessageBox::StandardButton::Ok,
                                       QMessageBox::StandardButton::Cancel);

    if(answer == QMessageBox::Ok)
    {
        gameEngine_.startGame();
    }
    else
    {
        exit(0);
    }
}

void GameWindow::redrawSnakeSlot()
{
    Drawer::eraseSnake(gameEngine_.getSnake().getSnakeSquaresGraphicalRectItems());
    Drawer::drawSnake(gameEngine_.getSnake().getPositions(), gameEngine_.getSnake().getSnakeSquaresGraphicalRectItems());
}

void GameWindow::speedSliderValueChangedSlot()
{
    gameEngine_.setGameSpeedLevel();
}
