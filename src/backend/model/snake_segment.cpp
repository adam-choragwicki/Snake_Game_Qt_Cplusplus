#include "snake_segment.h"

SnakeSegment::SnakeSegment(const Coordinates& coordinates, const Direction& movementDirection) : coordinates_(coordinates), movementDirection_(movementDirection)
{}

void SnakeSegment::move()
{
    switch(movementDirection_)
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
}
