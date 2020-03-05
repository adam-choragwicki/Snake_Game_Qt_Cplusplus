#include "game_window.h"
#include "ui_game_window.h"
#include "utilities.h"
#include <drawer.h>

void GameWindow::InitializeGameplayScene()
{
    m_pUi->graphicsView->setScene(&m_Scene);
    m_Scene.setBackgroundBrush(QBrush(Qt::black));

    int const sceneWidth = 1560;
    int const sceneHeight = 810;

    m_Scene.setSceneRect(0,0, sceneWidth, sceneHeight);
}

GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent), m_pUi(new Ui::MainWindow)
{
    m_pUi->setupUi(this);

    setFocus(Qt::ActiveWindowFocusReason);
    this->setWindowTitle("Snake");

    InitializeGameplayScene();

    DrawGameArena();

    Drawer::SetScene(&m_Scene);

    m_Food.GenerateAndPlace();

    Drawer::DrawSnake(m_Snake.GetPositions());
    Drawer::DrawFood(m_Food.GetPosition());

    connect(&m_UpdaterTimer, &QTimer::timeout, this, &GameWindow::GameTick);
    m_UpdaterTimer.start(GAME_TICK);

    //DrawAllSquares();
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
        if(currentDirection != Direction::right)
        {
            m_Snake.SetNextDirection(Direction::left);
        }
        qDebug() << "LEFT";
        break;

    case Qt::Key_W:
        if(currentDirection != Direction::down)
        {
            m_Snake.SetNextDirection(Direction::up);
        }
        qDebug() << "UP";
        break;

    case Qt::Key_S:
        if(currentDirection != Direction::up)
        {
            m_Snake.SetNextDirection(Direction::down);
        }
        qDebug() << "DOWN";
        break;

    case Qt::Key_D:
        if(currentDirection != Direction::left)
        {
            m_Snake.SetNextDirection(Direction::right);
        }
        qDebug() << "RIGHT";
        break;

    default:
        qDebug() << "Wrong key pressed";
    }
}

void GameWindow::GameTick()
{
    m_Snake.Move();
    m_Snake.SetDirection(m_Snake.GetNextDirection());

    //if snake hits a wall
    if(m_Snake.GetHeadPosition().x() > MAXIMUM_COLUMN ||
            m_Snake.GetHeadPosition().x() < MINIMUM_ROW_COLUMN ||
            m_Snake.GetHeadPosition().y() > MAXIMUM_ROW ||
            m_Snake.GetHeadPosition().y() < MINIMUM_ROW_COLUMN)
    {
        m_UpdaterTimer.stop();

        int answer = QMessageBox::question(this,
                                           "Game Over",
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
        return;
    }

    //if m_pSnake hit itself
    QVector<QPoint> m_pSnakePositions = m_Snake.GetPositions();
    m_pSnakePositions.removeFirst();
    QPoint headPosition = m_Snake.GetHeadPosition();

    if(m_pSnakePositions.contains(headPosition))
    {
        m_UpdaterTimer.stop();
        int answer = QMessageBox::question(this,
                                           "Game Over",
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
        return;
    }

    //if m_pSnake head hits m_pFood point
    if(m_Snake.GetHeadPosition() == m_Food.GetPosition())
    {
        Drawer::EraseFood();
        m_Snake.Grow();
        m_Food.GenerateAndPlace();
        Drawer::DrawFood(m_Food.GetPosition());
    }

    //redraw m_pSnake
    Drawer::EraseSnake();
    Drawer::DrawSnake(m_Snake.GetPositions());
}

GameWindow::~GameWindow()
{
    delete m_pUi;
}
