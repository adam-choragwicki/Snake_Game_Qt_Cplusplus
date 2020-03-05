#include "game_window.h"
#include "ui_game_window.h"

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
    m_pScene->setSceneRect(0,0,1560,810);

    DrawArena();

    m_pSnake = new Snake;
    m_pFood = new Food;
    m_pDrawer = new Drawer(m_pScene);
    m_pUpdaterTimer = new QTimer;

    m_pFood->GenerateAndPlace();

    m_pDrawer->DrawSnake(m_pSnake->GetPositions());
    m_pDrawer->DrawFood(m_pFood->GetPosition());

    connect(m_pUpdaterTimer, &QTimer::timeout, this, &GameWindow::GameTick);
    m_pUpdaterTimer->start(100);
}

void GameWindow::DrawAllSquares()
{
    QPen redPen(Qt::red);
    QPen bluePen(Qt::blue);
    QBrush greenBrush(Qt::green);

    for(int i = 0 ; i < 50; i++)
    {
        for(int j = 0; j < 25; j++)
        {
            if(i % 2 == 0)  //even
            {
                //shift 30 right and down
                m_pScene->addRect(30 + i * 30,
                                  30 + j * 30,
                                  m_SquareSize,
                                  m_SquareSize,
                                  redPen,
                                  greenBrush);
            }
            else //odd
            {
                //shift 30 right and down
                m_pScene->addRect(30 + i * 30,
                                  30 + j * 30,
                                  m_SquareSize,
                                  m_SquareSize,
                                  bluePen,
                                  greenBrush);
            }
        }
    }
}

void GameWindow::DrawArena()
{
    QPen pen(Qt::white, 30);

    m_pScene->addLine(15, 15,1560-15, 15, pen);
    m_pScene->addLine(15, 15,15, 810-15, pen);
    m_pScene->addLine(1560-15, 15, 1560-15, 810-15, pen);
    m_pScene->addLine(15, 810-15, 1560-15, 810-15, pen);
}

void GameWindow::RestartGame()
{
    m_pSnake->ClearPositions();
    m_pSnake->Initialize();

    m_pUpdaterTimer->start(100);
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    int currentDirection = m_pSnake->GetDirection();

    switch(event->key())
    {
    case Qt::Key_A:
        if(currentDirection != Snake::right)
        {
            m_pSnake->SetNextDirection(Snake::left);
        }
        qDebug() << "LEFT";
        break;

    case Qt::Key_W:
        if(currentDirection != Snake::down)
        {
            m_pSnake->SetNextDirection(Snake::up);
        }
        qDebug() << "UP";
        break;

    case Qt::Key_S:
        if(currentDirection != Snake::up)
        {
            m_pSnake->SetNextDirection(Snake::down);
        }
        qDebug() << "DOWN";
        break;

    case Qt::Key_D:
        if(currentDirection != Snake::left)
        {
            m_pSnake->SetNextDirection(Snake::right);
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
    if(m_pSnake->GetHeadPosition().x() > 49 ||
            m_pSnake->GetHeadPosition().x() < 0 ||
            m_pSnake->GetHeadPosition().y() > 24 ||
            m_pSnake->GetHeadPosition().y() < 0)
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
