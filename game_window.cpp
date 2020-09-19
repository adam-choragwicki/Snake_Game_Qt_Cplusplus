#include "game_window.h"
#include "ui_game_window.h"
#include <drawer.h>

GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent), m_pUi(new Ui::GameWindow)
{
    m_pUi->setupUi(this);

    setFocus(Qt::ActiveWindowFocusReason);
    this->setWindowTitle("Snake");

    InitializeGameplayScene();

    Drawer::SetScene(&m_Scene);

    Drawer::DrawGameArena();

    m_Food.GenerateAndPlace();

    Drawer::DrawSnake(m_Snake.GetPositions(), m_Snake.GetSnakeSquaresGraphicalRectItems());

    connect(&m_GameTickTimer, &QTimer::timeout, this, &GameWindow::GameTick);

    StartGame();
}

void GameWindow::InitializeGameplayScene()
{
    m_pUi->m_GraphicsView->setScene(&m_Scene);
    m_Scene.setBackgroundBrush(QBrush(Qt::black));

    const int sceneWidth = Drawer::COLUMNS_COUNT * Drawer::SQUARE_SIZE + 2 * Drawer::WALL_THICKNESS;
    const int sceneHeight = Drawer::ROWS_COUNT * Drawer::SQUARE_SIZE + 2 * Drawer::WALL_THICKNESS;

    m_Scene.setSceneRect(0,0, sceneWidth, sceneHeight);
}

void GameWindow::StartGame()
{
    m_Snake.Reset();
    SetGameSpeedLevel(m_pUi->m_SpeedHorizontalSlider->value());
    m_GameTickTimer.start();
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    Snake::Direction currentDirection = m_Snake.GetDirection();

    int sliderValue = m_pUi->m_SpeedHorizontalSlider->value();

    switch(event->key())
    {
    case Qt::Key_A:
    case Qt::Key_Left:
        if(currentDirection != Snake::Direction::right)
        {
            m_Snake.SetNextDirection(Snake::Direction::left);
        }
        break;

    case Qt::Key_W:
    case Qt::Key_Up:
        if(currentDirection != Snake::Direction::down)
        {
            m_Snake.SetNextDirection(Snake::Direction::up);
        }
        break;

    case Qt::Key_S:
    case Qt::Key_Down:
        if(currentDirection != Snake::Direction::up)
        {
            m_Snake.SetNextDirection(Snake::Direction::down);
        }
        break;

    case Qt::Key_D:
    case Qt::Key_Right:
        if(currentDirection != Snake::Direction::left)
        {
            m_Snake.SetNextDirection(Snake::Direction::right);
        }
        break;

    case Qt::Key_Plus:
        //Subtracting means increasing speed
        m_pUi->m_SpeedHorizontalSlider->setValue(sliderValue - 1);
        break;

    case Qt::Key_Minus:
        //Adding means decreasing speed
        m_pUi->m_SpeedHorizontalSlider->setValue(sliderValue + 1);
        break;

    default:
        qDebug() << "Wrong key pressed";
    }
}

void GameWindow::CheckSnakeCollisionWithFoodSquare()
{
    if(m_Snake.GetHeadPosition() == m_Food.GetPosition())
    {
        Drawer::EraseFood(m_Food.GetFoodSquareGraphicalRectItem());
        m_Food.GenerateAndPlace();
        m_Snake.Grow();
    }
}

void GameWindow::CheckSnakeCollisionWithWall()
{
    /*Check if snake hit a wall*/
    if(m_Snake.GetHeadPosition().x() > Drawer::MAXIMUM_COLUMN ||
            m_Snake.GetHeadPosition().x() < Drawer::MINIMUM_ROW_COLUMN ||
            m_Snake.GetHeadPosition().y() > Drawer::MAXIMUM_ROW ||
            m_Snake.GetHeadPosition().y() < Drawer::MINIMUM_ROW_COLUMN)
    {
        m_GameTickTimer.stop();

        int answer = QMessageBox::question(this,
                                           "Snake has hit the wall",
                                           "Restart?",
                                           QMessageBox::StandardButton::Ok,
                                           QMessageBox::StandardButton::Cancel);

        if(answer == QMessageBox::Ok)
        {
            StartGame();
        }
        else
        {
            exit(0);
        }
    }
}

void GameWindow::CheckSnakeCollisionWithItself()
{
    /*Check if snake hit itself*/
    QVector<QPoint> snakePositions = m_Snake.GetPositions();

    /*Remove head position from snake positions so it is not taken into account here*/
    snakePositions.removeFirst();

    QPoint headPosition = m_Snake.GetHeadPosition();

    if(snakePositions.contains(headPosition))
    {
        m_GameTickTimer.stop();
        int answer = QMessageBox::question(this,
                                           "Snake has hit itself",
                                           "Restart?",
                                           QMessageBox::StandardButton::Ok,
                                           QMessageBox::StandardButton::Cancel);

        if(answer == QMessageBox::Ok)
        {
            StartGame();
        }
        else
        {
            exit(0);
        }
    }
}

void GameWindow::RedrawSnake()
{
    Drawer::EraseSnake(m_Snake.GetSnakeSquaresGraphicalRectItems());
    Drawer::DrawSnake(m_Snake.GetPositions(), m_Snake.GetSnakeSquaresGraphicalRectItems());
}

void GameWindow::GameTick()
{
    m_Snake.Move();
    m_Snake.SetDirection(m_Snake.GetNextDirection());

    CheckSnakeCollisionWithWall();
    CheckSnakeCollisionWithItself();
    CheckSnakeCollisionWithFoodSquare();

    RedrawSnake();
}

GameWindow::~GameWindow()
{
    delete m_pUi;
}

void GameWindow::on_m_SpeedHorizontalSlider_valueChanged(int value)
{
    SetGameSpeedLevel(value);
}

void GameWindow::SetGameSpeedLevel(int speedLevel)
{
    const int TIME_OFFSET = 20;

    m_GameTickTimer.setInterval(TIME_OFFSET + speedLevel * 20);
}
