#include "snake.h"

Snake::Snake()
{
    reset();
}

void Snake::move()
{
    segments_.removeLast();

    switch(direction_)
    {
        case Direction::left:
            segments_.prepend(Segment(headPosition_.x() - 1, headPosition_.y()));
            break;

        case Direction::right:
            segments_.prepend(Segment(headPosition_.x() + 1, headPosition_.y()));
            break;

        case Direction::up:
            segments_.prepend(Segment(headPosition_.x(), headPosition_.y() - 1));
            break;

        case Direction::down:
            segments_.prepend(Segment(headPosition_.x(), headPosition_.y() + 1));
            break;
    }

    updateHeadPosition();
}

void Snake::grow()
{
    switch(direction_)
    {
        case Direction::left:
            segments_.prepend(Segment(headPosition_.x() - 1, headPosition_.y()));
            break;

        case Direction::right:
            segments_.prepend(Segment(headPosition_.x() + 1, headPosition_.y()));
            break;

        case Direction::up:
            segments_.prepend(Segment(headPosition_.x(), headPosition_.y() - 1));
            break;

        case Direction::down:
            segments_.prepend(Segment(headPosition_.x(), headPosition_.y() + 1));
            break;
    }

    updateHeadPosition();
}

void Snake::reset()
{
    segments_.clear();
    segments_.squeeze();

    for(const auto& position: startingPositions_)
    {
        segments_.emplaceBack(position);
    }

    headPosition_ = segments_.front().getCoordinates();

    setDirection(Direction::left);
    setNextDirection(direction_);
}
