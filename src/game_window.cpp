#include "game_window.h"
#include "ui_game_window.h"
#include "drawer.h"
#include "config.h"

GameWindow::GameWindow(QWidget* parent) : QMainWindow(parent), ui_(new Ui::GameWindow)
{
    ui_->setupUi(this);
    setWindowTitle("Snake");
    setFocus(Qt::ActiveWindowFocusReason);

    initializeGameplayAreaScene();
    Drawer::drawGameArena();

    QObject::connect(ui_->slider_Speed, &QSlider::valueChanged, this, &GameWindow::speedSliderValueChangedSlot);

    gameEngine_ = std::make_unique<GameEngine>(ui_->slider_Speed);
    QObject::connect(gameEngine_.get(), &GameEngine::dialogRestartGameSignal, this, &GameWindow::dialogRestartGameSlot);
}

GameWindow::~GameWindow()
{
    delete ui_;
}

void GameWindow::initializeGameplayAreaScene()
{
    ui_->graphicsView->setScene(&scene_);
    ui_->graphicsView->setRenderHint(QPainter::Antialiasing);
    scene_.setBackgroundBrush(QBrush(Qt::black));

    const int sceneWidth = GameParameters::Arena::columnCount * GameParameters::snakeSegmentSize + 2 * GameParameters::Arena::wallThickness;
    const int sceneHeight = GameParameters::Arena::rowsCount * GameParameters::snakeSegmentSize + 2 * GameParameters::Arena::wallThickness;

    scene_.setSceneRect(0, 0, sceneWidth, sceneHeight);

    Drawer::setScene(&scene_);
}

void GameWindow::keyPressEvent(QKeyEvent* event)
{
    switch(event->key())
    {
        case Qt::Key_Left:
        case Qt::Key_A:
            gameEngine_->processKeyPress(Key::left);
            break;

        case Qt::Key_Right:
        case Qt::Key_D:
            gameEngine_->processKeyPress(Key::right);
            break;

        case Qt::Key_Up:
        case Qt::Key_W:
            gameEngine_->processKeyPress(Key::up);
            break;

        case Qt::Key_Down:
        case Qt::Key_S:
            gameEngine_->processKeyPress(Key::down);
            break;

        case Qt::Key_Plus:
            gameEngine_->processKeyPress(Key::plus);
            break;

        case Qt::Key_Minus:
            gameEngine_->processKeyPress(Key::minus);
            break;

        case Qt::Key_Space:
            gameEngine_->processKeyPress(Key::space);
            break;
    }
}

void GameWindow::keyReleaseEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Space)
    {
        gameEngine_->deactivateSpeedBoost();
    }
}

void GameWindow::dialogRestartGameSlot()
{
    int response = QMessageBox::question(this, "Game over", "Restart?", QMessageBox::StandardButton::Ok, QMessageBox::StandardButton::Cancel);

    if(response == QMessageBox::Ok)
    {
        gameEngine_ = std::make_unique<GameEngine>(ui_->slider_Speed);
        QObject::connect(gameEngine_.get(), &GameEngine::dialogRestartGameSignal, this, &GameWindow::dialogRestartGameSlot);
    }
    else
    {
        exit(0);
    }
}

void GameWindow::speedSliderValueChangedSlot()
{
    gameEngine_->setGameSpeedLevel();
}
