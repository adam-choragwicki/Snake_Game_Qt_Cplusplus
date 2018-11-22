#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->setBackgroundBrush(QBrush(Qt::black)); //background is black
    scene->setSceneRect(0,0,1560,810);

    drawArena();

    snake = new Snake;
    food = new Food;
    drawer = new Drawer(scene);
    updaterTimer = new QTimer;

    food->generateAndPlace();

    drawer->drawSnake(snake->getPositions());
    drawer->drawFood(food->getPosition());

    connect(updaterTimer, SIGNAL(timeout()), this, SLOT(updater()));
    updaterTimer->start(100);
}

void MainWindow::drawAllSquares()
{
    QPen red_pen(Qt::red);
    QBrush red_brush(Qt::red);

    QPen green_pen(Qt::green);
    QBrush green_brush(Qt::green);

    QPen blue_pen(Qt::blue);
    QBrush blue_brush(Qt::blue);

    for(int i=0 ; i<50; i++)
    {
        for(int j=0; j<25; j++)
        {
            if(i%2 ==0)  //even
            {
                //shift 30 right and down
                scene->addRect(30 + i*30, 30 + j*30, square_size,square_size, red_pen, green_brush);
            }
            else //odd
            {
                //shift 30 right and down
                scene->addRect(30 + i*30, 30 + j*30, square_size,square_size, blue_pen, green_brush);
            }
        }
    }
}

void MainWindow::drawArena()
{
     scene->addLine(15,15,1560-15,15, QPen(Qt::white,30));
     scene->addLine(15,15,15,810-15, QPen(Qt::white,30));
     scene->addLine(1560-15,15,1560-15,810-15, QPen(Qt::white,30));
     scene->addLine(15,810-15,1560-15,810-15, QPen(Qt::white,30));
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int currentDirection = snake->getDirection();

    switch(event->key())
    {
    case Qt::Key_A:
        if(currentDirection != Snake::right)
            snake->setNextDirection(Snake::left);
        qDebug() << "LEFT";
        break;
    case Qt::Key_W:
        if(currentDirection != Snake::down)
        snake->setNextDirection(Snake::up);
        qDebug() << "UP";
        break;
    case Qt::Key_S:
        if(currentDirection != Snake::up)
        snake->setNextDirection(Snake::down);
        qDebug() << "DOWN";
        break;
    case Qt::Key_D:
        if(currentDirection != Snake::left)
        snake->setNextDirection(Snake::right);
        qDebug() << "RIGHT";
        break;
    default:
        qDebug() << "Wrong key pressed";
    }
}

void MainWindow::updater()
{
    snake->move();

    //if snake hit wall
    if(snake->getHeadPosition().x() > 49 ||
            snake->getHeadPosition().x() < 0 ||
            snake->getHeadPosition().y() > 24 ||
            snake->getHeadPosition().y() < 0)
    {
        updaterTimer->stop();
    }

    //if snake hit itself
    QVector<QPoint> snakePositions = snake->getPositions();
    snakePositions.removeFirst();
    QPoint headPosition = snake->getHeadPosition();

    if(snakePositions.contains(headPosition))
    {
        updaterTimer->stop();
        return;
    }

    snake->setDirection(snake->getNextDirection());

    //if snake head hits food point
    if(snake->getHeadPosition() == food->getPosition())
    {
        drawer->eraseFood();
        snake->grow();
        food->generateAndPlace();
        drawer->drawFood(food->getPosition());
    }

    //redraw snake
    drawer->eraseSnake();
    drawer->drawSnake(snake->getPositions());
}

MainWindow::~MainWindow()
{
    delete ui;
}
