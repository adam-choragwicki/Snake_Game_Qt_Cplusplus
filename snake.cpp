#include "snake.h"

Snake::Snake()
{
    initialize();
}

void Snake::initialize()
{
    positions.append(QPoint(25,12));
    positions.append(QPoint(24,12));
    positions.append(QPoint(23,12));

    headPosition.setX(positions.front().x()); //initial head position x
    headPosition.setY(positions.front().y()); //initial head position y

    setDirection(right);
    setNextDirection(right);
}

void Snake::move()
{
    switch(direction)
    {
    case left:
        positions.removeLast(); //delete last element
        positions.prepend(QPoint(headPosition.x() - 1, headPosition.y()));
        setHeadPosition(QPoint(positions.front()));
        break;
    case up:
        positions.removeLast(); //delete last element
        positions.prepend(QPoint(headPosition.x(), headPosition.y() - 1));
        setHeadPosition(QPoint(positions.front()));
        break;
    case down:
        positions.removeLast(); //delete last element
        positions.prepend(QPoint(headPosition.x(), headPosition.y() + 1));
        setHeadPosition(QPoint(positions.front()));
        break;
    case right:
        positions.removeLast(); //delete last element
        positions.prepend(QPoint(headPosition.x() + 1, headPosition.y()));
        setHeadPosition(QPoint(positions.front()));
        break;
    default:
        qDebug() << "Wrong direction in Snake::move(int direction)";
    }
}

void Snake::grow()
{
    switch(direction)
    {
    case left:
        positions.prepend(QPoint(headPosition.x() - 1, headPosition.y()));
        setHeadPosition(QPoint(positions.front()));
        break;
    case up:
        positions.prepend(QPoint(headPosition.x(), headPosition.y() - 1));
        setHeadPosition(QPoint(positions.front()));
        break;
    case down:
        positions.prepend(QPoint(headPosition.x(), headPosition.y() + 1));
        setHeadPosition(QPoint(positions.front()));
        break;
    case right:
        positions.prepend(QPoint(headPosition.x() + 1, headPosition.y()));
        setHeadPosition(QPoint(positions.front()));
        break;
    default:
        qDebug() << "Wrong direction in Snake::grow(int direction)";
    }
}

//used to restart game
void Snake::clearPositions()
{
    positions.clear();
    positions.squeeze();
}

void Snake::setHeadPosition(QPoint headPoint)
{
    headPosition = headPoint;
}

void Snake::setDirection(int dir)
{
    direction = dir;
}

void Snake::setNextDirection(int nextdir)
{
    nextDirection = nextdir;
}
