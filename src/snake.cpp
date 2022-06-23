#include "snake.h"
#include "drawer.h"

Snake::Snake()
{
    for(const auto& coordinates : startingCoordinates_)
    {
        segments_.emplaceBack(coordinates);
    }

    setDirection(Direction::left);
    setNextDirection(direction_);

    Drawer::drawSnake(*this);
}

Snake::~Snake()
{
    Drawer::eraseSnake(*this);
}

void Snake::moveForward()
{
    const Coordinates& headCoordinates = getHeadCoordinates();

    switch(direction_)
    {
        case Direction::left:
            segments_.prepend(Segment(headCoordinates.x - 1, headCoordinates.y));
            break;

        case Direction::right:
            segments_.prepend(Segment(headCoordinates.x + 1, headCoordinates.y));
            break;

        case Direction::up:
            segments_.prepend(Segment(headCoordinates.x, headCoordinates.y - 1));
            break;

        case Direction::down:
            segments_.prepend(Segment(headCoordinates.x, headCoordinates.y + 1));
            break;
    }

    /*Potential snake growing is inherently part of movement process*/
    checkAndProcessGrowth();
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
