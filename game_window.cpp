#include "game_window.h"
#include "ui_game_window.h"
#include "utilities.h"
#include <drawer.h>

GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent), m_pUi(new Ui::MainWindow)
{
    m_pUi->setupUi(this);

    setFocus(Qt::ActiveWindowFocusReason);
    this->setWindowTitle("Snake");

    InitializeGameplayScene();

    DrawGameArena();

    Drawer::SetScene(&m_Scene);

    m_Food.GenerateAndPlace();

    Drawer::DrawSnake(m_Snake.GetPositions(), m_Snake.GetSnakeSquaresGraphicalRectItems());

    connect(&m_UpdaterTimer, &QTimer::timeout, this, &GameWindow::GameTick);
    m_UpdaterTimer.start(GAME_TICK);
}

void GameWindow::InitializeGameplayScene()
{
    m_pUi->graphicsView->setScene(&m_Scene);
    m_Scene.setBackgroundBrush(QBrush(Qt::black));

    int const sceneWidth = COLUMNS_COUNT * SQUARE_SIZE + 2 * WALL_THICKNESS;
    int const sceneHeight = ROWS_COUNT * SQUARE_SIZE + 2 * WALL_THICKNESS;

    m_Scene.setSceneRect(0,0, sceneWidth, sceneHeight);
}

void GameWindow::DrawAllSquares()
{
    QBrush redBrush(Qt::red);
    QBrush greenBrush(Qt::green);

    for(int column = 0 ; column < COLUMNS_COUNT; column++)
    {
        for(int row = 0; row < ROWS_COUNT; row++)
        {
            /*Even columns*/
            if(column % 2 == 0)
            {
                if(row % 2 == 0)
                {
                    m_Scene.addRect(column * SQUARE_SIZE + SQUARE_SIZE,
                                    row * SQUARE_SIZE + SQUARE_SIZE,
                                    SQUARE_SIZE,
                                    SQUARE_SIZE,
                                    Qt::NoPen,
                                    redBrush);
                }
                else
                {
                    m_Scene.addRect(column * SQUARE_SIZE + SQUARE_SIZE,
                                    row * SQUARE_SIZE + SQUARE_SIZE,
                                    SQUARE_SIZE,
                                    SQUARE_SIZE,
                                    Qt::NoPen,
                                    greenBrush);
                }
            }
            /*Odd columns*/
            else
            {
                if(row % 2 == 0)
                {
                    m_Scene.addRect(column * SQUARE_SIZE + SQUARE_SIZE,
                                    row * SQUARE_SIZE + SQUARE_SIZE,
                                    SQUARE_SIZE,
                                    SQUARE_SIZE,
                                    Qt::NoPen,
                                    greenBrush);
                }
                else
                {
                    m_Scene.addRect(column * SQUARE_SIZE + SQUARE_SIZE,
                                    row * SQUARE_SIZE + SQUARE_SIZE,
                                    SQUARE_SIZE,
                                    SQUARE_SIZE,
                                    Qt::NoPen,
                                    redBrush);
                }
            }
        }
    }
}

void GameWindow::DrawGameArena()
{
    QPen pen(Qt::white, SQUARE_SIZE);

    /*Top wall*/
    m_Scene.addLine(LEFT_BORDER_X,
                    TOP_Y,
                    RIGHT_BORDER_X + RIGHT_BORDER_X_OFFSET,
                    TOP_Y,
                    pen);
    /*Left wall*/
    m_Scene.addLine(LEFT_BORDER_X,
                    TOP_Y,
                    LEFT_BORDER_X,
                    BOTTOM_Y + BOTTOM_Y_OFFSET,
                    pen);
    /*Bottom wall*/
    m_Scene.addLine(LEFT_BORDER_X,
                    BOTTOM_Y + BOTTOM_Y_OFFSET,
                    RIGHT_BORDER_X + RIGHT_BORDER_X_OFFSET,
                    BOTTOM_Y + BOTTOM_Y_OFFSET,
                    pen);
    /*Right wall*/
    m_Scene.addLine(RIGHT_BORDER_X + RIGHT_BORDER_X_OFFSET,
                    TOP_Y,
                    RIGHT_BORDER_X + RIGHT_BORDER_X_OFFSET,
                    BOTTOM_Y + BOTTOM_Y_OFFSET,
                    pen);
}

void GameWindow::RestartGame()
{
    m_Snake.Reset();
    m_UpdaterTimer.start(GAME_TICK);
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    Direction currentDirection = m_Snake.GetDirection();

    switch(event->key())
    {
    case Qt::Key_A:
    case Qt::Key_Left:
        if(currentDirection != Direction::right)
        {
            m_Snake.SetNextDirection(Direction::left);
        }
        break;

    case Qt::Key_W:
    case Qt::Key_Up:
        if(currentDirection != Direction::down)
        {
            m_Snake.SetNextDirection(Direction::up);
        }
        break;

    case Qt::Key_S:
    case Qt::Key_Down:
        if(currentDirection != Direction::up)
        {
            m_Snake.SetNextDirection(Direction::down);
        }
        break;

    case Qt::Key_D:
    case Qt::Key_Right:
        if(currentDirection != Direction::left)
        {
            m_Snake.SetNextDirection(Direction::right);
        }
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
    if(m_Snake.GetHeadPosition().x() > MAXIMUM_COLUMN ||
            m_Snake.GetHeadPosition().x() < MINIMUM_ROW_COLUMN ||
            m_Snake.GetHeadPosition().y() > MAXIMUM_ROW ||
            m_Snake.GetHeadPosition().y() < MINIMUM_ROW_COLUMN)
    {
        m_UpdaterTimer.stop();

        int answer = QMessageBox::question(this,
                                           "Snake has hit the wall",
                                           "Restart?",
                                           QMessageBox::StandardButton::Ok,
                                           QMessageBox::StandardButton::Cancel);

        if(answer == QMessageBox::Ok)
        {
            RestartGame();
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
        m_UpdaterTimer.stop();
        int answer = QMessageBox::question(this,
                                           "Snake has hit itself",
                                           "Restart?",
                                           QMessageBox::StandardButton::Ok,
                                           QMessageBox::StandardButton::Cancel);

        if(answer == QMessageBox::Ok)
        {
            RestartGame();
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
