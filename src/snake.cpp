#include "inc/snake.h"

Snake::Snake()
{
    positions_ = startingPositions_;
    headPosition_ = positions_.front();

    setDirection(Direction::right);
    setNextDirection(Direction::right);
}

void Snake::move()
{
    switch(direction_)
    {
    case Direction::left:
        positions_.removeLast(); //delete last element
        positions_.prepend(QPoint(headPosition_.x() - 1, headPosition_.y()));
        setHeadPosition(QPoint(positions_.front()));
        break;

    case Direction::up:
        positions_.removeLast(); //delete last element
        positions_.prepend(QPoint(headPosition_.x(), headPosition_.y() - 1));
        setHeadPosition(QPoint(positions_.front()));
        break;

    case Direction::down:
        positions_.removeLast(); //delete last element
        positions_.prepend(QPoint(headPosition_.x(), headPosition_.y() + 1));
        setHeadPosition(QPoint(positions_.front()));
        break;

    case Direction::right:
        positions_.removeLast(); //delete last element
        positions_.prepend(QPoint(headPosition_.x() + 1, headPosition_.y()));
        setHeadPosition(QPoint(positions_.front()));
        break;

    default:
        assert(false);
    }
}

void Snake::grow()
{
    switch(direction_)
    {
    case Direction::left:
        positions_.prepend(QPoint(headPosition_.x() - 1, headPosition_.y()));
        setHeadPosition(QPoint(positions_.front()));
        break;

    case Direction::up:
        positions_.prepend(QPoint(headPosition_.x(), headPosition_.y() - 1));
        setHeadPosition(QPoint(positions_.front()));
        break;

    case Direction::down:
        positions_.prepend(QPoint(headPosition_.x(), headPosition_.y() + 1));
        setHeadPosition(QPoint(positions_.front()));
        break;

    case Direction::right:
        positions_.prepend(QPoint(headPosition_.x() + 1, headPosition_.y()));
        setHeadPosition(QPoint(positions_.front()));
        break;

    default:
        assert(false);
    }
}

void Snake::reset()
{
    positions_.clear();
    positions_.squeeze();

    positions_ = startingPositions_;

    qDebug() << "Starting positions: " << startingPositions_;

    headPosition_ = positions_.front();

    setDirection(Direction::right);
    setNextDirection(Direction::right);
}
