#include "snake.h"

Snake::Snake()
{
    reset();
}

void Snake::move()
{
    switch(direction_)
    {
        case Direction::left:
            segments_.prepend(Segment(headCoordinates_.x - 1, headCoordinates_.y));
            break;

        case Direction::right:
            segments_.prepend(Segment(headCoordinates_.x + 1, headCoordinates_.y));
            break;

        case Direction::up:
            segments_.prepend(Segment(headCoordinates_.x, headCoordinates_.y - 1));
            break;

        case Direction::down:
            segments_.prepend(Segment(headCoordinates_.x, headCoordinates_.y + 1));
            break;
    }

    /*Potential snake growing is inherently part of movement process*/
    checkAndProcessGrowth();

    updateHeadCoordinates();
}

void Snake::processFoodEaten()
{
    segments_[0].setIsFoodInside(true);
}

void Snake::checkAndProcessGrowth()
{
    if(segments_.back().isFoodInside())
    {
        grow();
    }
    else
    {
        removeTail();
    }
}

void Snake::grow()
{
    /*Growing is actually not removing the tail segment if there is food inside it*/
    segments_.back().setIsFoodInside(false);
}

void Snake::removeTail()
{
    segments_.removeLast();
}

void Snake::reset()
{
    segments_.clear();
    segments_.squeeze();

    for(const auto& coordinates : startingCoordinates_)
    {
        segments_.emplaceBack(coordinates);
    }

    headCoordinates_ = segments_.front().getCoordinates();

    setDirection(Direction::left);
    setNextDirection(direction_);
}
