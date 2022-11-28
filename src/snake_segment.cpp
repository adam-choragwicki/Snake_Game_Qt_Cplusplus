#include "snake_segment.h"

SnakeSegment::SnakeSegment(const Coordinates& coordinates) : coordinates_(coordinates)
{

}

SnakeSegment::~SnakeSegment()
{

}

Direction SnakeSegment::move(Direction direction)
{
    switch(direction)
    {
        case Direction::LEFT:
            coordinates_ += {-1, 0};
            break;

        case Direction::RIGHT:
            coordinates_ += {+1, 0};
            break;

        case Direction::UP:
            coordinates_ += {0, -1};
            break;

        case Direction::DOWN:
            coordinates_ += {0, +1};
            break;
    }

    return direction;
}

HeadSegment::HeadSegment(const Coordinates& coordinates, Direction& direction) : SnakeSegment(coordinates), direction_(direction)
{

}
