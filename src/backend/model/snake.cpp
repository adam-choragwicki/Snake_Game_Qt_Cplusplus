#include "snake.h"
#include "game_parameters.h"
#include "snake_iterator.h"

Snake::Snake()
{
    segments_.reserve(Config::Arena::TOTAL_FIELDS_COUNT);
    nextHeadDirection_ = GameParameters::Snake::STARTING_DIRECTION;

    createHead();

    while(segments_.size() != GameParameters::Snake::STARTING_TOTAL_SEGMENT_COUNT)
    {
        appendSegment();
    }
}

void Snake::createHead()
{
    segments_.emplace_back(GameParameters::Snake::STARTING_HEAD_COORDINATES, GameParameters::Snake::STARTING_DIRECTION);
}

void Snake::moveForward()
{
    for(SnakeReverseIterator snakeIterator = createIterator(); !snakeIterator.isDone(); snakeIterator.advance())
    {
        if(snakeIterator.hasNext())
        {
            snakeIterator.current().move();
            snakeIterator.current().setMovementDirection(snakeIterator.next().getMovementDirection());
        }
        else
        {
            snakeIterator.current().move();
        }
    }

    if(growFlag_)
    {
        appendSegment();
        growFlag_ = false;
    }

    getHead().setMovementDirection(nextHeadDirection_);
}

void Snake::eatFood()
{
    if(!growFlag_)
    {
        growFlag_ = true;
    }
    else
    {
        throw std::runtime_error("Error, trying to double set grow flag");
    }
}

void Snake::appendSegment()
{
    if(segments_.empty())
    {
        throw std::runtime_error("Error, cannot append segment to 0-length snake");
    }

    const Coordinates tailCoordinates = getTailCoordinates();
    const Direction tailMovementDirection = getTail().getMovementDirection();

    auto addSegment = [this, &tailMovementDirection](const Coordinates& coordinates)
    {
        segments_.emplace_back(coordinates, tailMovementDirection);
    };

    if(tailMovementDirection == Direction::LEFT)
    {
        addSegment(tailCoordinates + std::pair{+1, 0});
    }
    else if(tailMovementDirection == Direction::RIGHT)
    {
        addSegment(tailCoordinates + std::pair{-1, 0});
    }
    else if(tailMovementDirection == Direction::UP)
    {
        addSegment(tailCoordinates + std::pair{0, +1});
    }
    else if(tailMovementDirection == Direction::DOWN)
    {
        addSegment(tailCoordinates + std::pair{0, -1});
    }
}

std::vector<Coordinates> Snake::getAllSegmentsCoordinates() const
{
    std::vector<Coordinates> allSegmentsCoordinates;

    for(const auto& segment : segments_)
    {
        allSegmentsCoordinates.push_back(segment.getCoordinates());
    }

    return allSegmentsCoordinates;
}

std::vector<Coordinates> Snake::getAllSegmentsCoordinatesExceptForHead() const
{
    std::vector<Coordinates> allSegmentsCoordinates = getAllSegmentsCoordinates();
    return {allSegmentsCoordinates.begin() + 1, allSegmentsCoordinates.end()};
}

std::ostream& operator<<(std::ostream& os, const Snake& snake)
{
    for(const auto& segment : snake.segments_)
    {
        os << segment.getCoordinates();
    }

    return os;
}

void Snake::setNextHeadDirection(const Direction& nextDirection)
{
    switch(nextDirection)
    {
        case Direction::LEFT:
            if(getMovementDirection() != Direction::RIGHT)
            {
                nextHeadDirection_ = Direction::LEFT;
            }
            break;

        case Direction::RIGHT:
            if(getMovementDirection() != Direction::LEFT)
            {
                nextHeadDirection_ = Direction::RIGHT;
            }
            break;

        case Direction::UP:
            if(getMovementDirection() != Direction::DOWN)
            {
                nextHeadDirection_ = Direction::UP;
            }
            break;

        case Direction::DOWN:
            if(getMovementDirection() != Direction::UP)
            {
                nextHeadDirection_ = Direction::DOWN;
            }
    }
}

SnakeReverseIterator Snake::createIterator()
{
    return SnakeReverseIterator(segments_);
}
