#include "game_window.h"
#include "ui_game_window.h"
#include "utilities.h"

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    m_pUi(new Ui::MainWindow)
{
    m_pUi->setupUi(this);
    setFocus(Qt::ActiveWindowFocusReason);
    this->setWindowTitle("Snake");

    m_pScene = new QGraphicsScene(this);
    m_pUi->graphicsView->setScene(m_pScene);
    m_pScene->setBackgroundBrush(QBrush(Qt::black)); //background is black

    int const sceneWidth = 1560;
    int const sceneHeight = 810;

    m_pScene->setSceneRect(0,0,sceneWidth,sceneHeight);

    DrawGameArena();

    m_pSnake = new Snake;
    m_pFood = new Food;
    m_pDrawer = new Drawer(m_pScene);
    m_pUpdaterTimer = new QTimer;

    m_pFood->GenerateAndPlace();

    m_pDrawer->DrawSnake(m_pSnake->GetPositions());
    m_pDrawer->DrawFood(m_pFood->GetPosition());

    connect(m_pUpdaterTimer, &QTimer::timeout, this, &GameWindow::GameTick);
    m_pUpdaterTimer->start(GAME_TICK);

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
                    m_pScene->addRect(column * SQUARE_SIZE + SQUARE_SIZE,
                                      row * SQUARE_SIZE + SQUARE_SIZE,
                                      SQUARE_SIZE,
                                      SQUARE_SIZE,
                                      Qt::NoPen,
                                      redBrush);
                }
                else
                {
                    m_pScene->addRect(column * SQUARE_SIZE + SQUARE_SIZE,
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
                    m_pScene->addRect(column * SQUARE_SIZE + SQUARE_SIZE,
                                      row * SQUARE_SIZE + SQUARE_SIZE,
                                      SQUARE_SIZE,
                                      SQUARE_SIZE,
                                      Qt::NoPen,
                                      greenBrush);
                }
                else
                {
                    m_pScene->addRect(column * SQUARE_SIZE + SQUARE_SIZE,
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
    m_pScene->addLine(LEFT_BORDER_X,
                      TOP_Y,
                      RIGHT_BORDER_X + RIGHT_BORDER_X_OFFSET,
                      TOP_Y,
                      pen);
    /*Left wall*/
    m_pScene->addLine(LEFT_BORDER_X,
                      TOP_Y,
                      LEFT_BORDER_X,
                      BOTTOM_Y + BOTTOM_Y_OFFSET,
                      pen);
    /*Bottom wall*/
    m_pScene->addLine(LEFT_BORDER_X,
                      BOTTOM_Y + BOTTOM_Y_OFFSET,
                      RIGHT_BORDER_X + RIGHT_BORDER_X_OFFSET,
                      BOTTOM_Y + BOTTOM_Y_OFFSET,
                      pen);
    /*Right wall*/
    m_pScene->addLine(RIGHT_BORDER_X + RIGHT_BORDER_X_OFFSET,
                      TOP_Y,
                      RIGHT_BORDER_X + RIGHT_BORDER_X_OFFSET,
                      BOTTOM_Y + BOTTOM_Y_OFFSET,
                      pen);
}

void GameWindow::RestartGame()
{
    m_pSnake->Reset();

    m_pUpdaterTimer->start(GAME_TICK);
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    Direction currentDirection = m_pSnake->GetDirection();

    switch(event->key())
    {
    case Qt::Key_A:
        if(currentDirection != Direction::right)
        {
            m_pSnake->SetNextDirection(Direction::left);
        }
        qDebug() << "LEFT";
        break;

    case Qt::Key_W:
        if(currentDirection != Direction::down)
        {
            m_pSnake->SetNextDirection(Direction::up);
        }
        qDebug() << "UP";
        break;

    case Qt::Key_S:
        if(currentDirection != Direction::up)
        {
            m_pSnake->SetNextDirection(Direction::down);
        }
        qDebug() << "DOWN";
        break;

    case Qt::Key_D:
        if(currentDirection != Direction::left)
        {
            m_pSnake->SetNextDirection(Direction::right);
        }
        qDebug() << "RIGHT";
        break;

    default:
        qDebug() << "Wrong key pressed";
    }
}

void GameWindow::GameTick()
{
    m_pSnake->Move();
    m_pSnake->SetDirection(m_pSnake->GetNextDirection());

    //if snake hits a wall
    if(m_pSnake->GetHeadPosition().x() > MAXIMUM_COLUMN ||
            m_pSnake->GetHeadPosition().x() < MINIMUM_ROW_COLUMN ||
            m_pSnake->GetHeadPosition().y() > MAXIMUM_ROW ||
            m_pSnake->GetHeadPosition().y() < MINIMUM_ROW_COLUMN)
    {
        m_pUpdaterTimer->stop();

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
    QVector<QPoint> m_pSnakePositions = m_pSnake->GetPositions();
    m_pSnakePositions.removeFirst();
    QPoint headPosition = m_pSnake->GetHeadPosition();

    if(m_pSnakePositions.contains(headPosition))
    {
        m_pUpdaterTimer->stop();
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
    if(m_pSnake->GetHeadPosition() == m_pFood->GetPosition())
    {
        m_pDrawer->EraseFood();
        m_pSnake->Grow();
        m_pFood->GenerateAndPlace();
        m_pDrawer->DrawFood(m_pFood->GetPosition());
    }

    //redraw m_pSnake
    m_pDrawer->EraseSnake();
    m_pDrawer->DrawSnake(m_pSnake->GetPositions());
}

GameWindow::~GameWindow()
{
    delete m_pUi;
}
