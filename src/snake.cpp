#include "snake.h"

Snake::Snake()
{
    segments_.emplace_back(std::make_unique<HeadSegment>(startingCoordinates_.at(0), direction_));

    for(int i = 1; i < startingCoordinates_.size(); ++i)
    {
        addSegment(startingCoordinates_.at(i));
    }

    setDirection(Direction::LEFT);
    setNextDirection(direction_);
}

void Snake::moveForward()
{
    Coordinates previousSegmentCoordinates = getHeadCoordinates();
    segments_.front()->move(direction_);

    const Coordinates& tailCoordinates = getTailCoordinates();

    /*Necessary for extending tail in proper direction*/
    Direction tailDirection;

    for(auto iter = segments_.begin() + 1; iter != segments_.end(); ++iter)
    {
        auto& snakeSegment = *iter;
        Coordinates currentSegmentCoordinates = snakeSegment->getCoordinates();
        Direction moveDirection = calculateSegmentDirection(previousSegmentCoordinates, currentSegmentCoordinates);

        if(currentSegmentCoordinates == tailCoordinates)
        {
            tailDirection = moveDirection;
        }

        snakeSegment->move(moveDirection);
        previousSegmentCoordinates = currentSegmentCoordinates;
    }

    shiftFoodInsideSnake(tailDirection);

    emit positionChangedEvent();
}

void Snake::shiftFoodInsideSnake(Direction& tailSegmentDirection)
{
    const Coordinates& headCoordinates = getHeadCoordinates();
    const Coordinates& tailCoordinates = getTailCoordinates();

    /*Iterate from back to front, shifting food inside snake*/
    for(int i = segments_.size() - 1; i >= 0; --i)
    {
        auto& segment = segments_.at(i);
        const Coordinates& segmentCoordinates = segment->getCoordinates();

        if(segmentCoordinates == headCoordinates)
        {
            if(segment->isFoodInside())
            {
                segments_.at(i + 1)->setIsFoodInside(true);
                segments_.at(i)->setIsFoodInside(false);
            }
            else
            {
                segments_.at(i + 1)->setIsFoodInside(false);
            }
        }
        else if(segmentCoordinates == tailCoordinates)
        {
            if(segment->isFoodInside())
            {
                segment->setIsFoodInside(false);
                grow(tailSegmentDirection);
            }
        }
        else
        {
            if(segment->isFoodInside())
            {
                segments_.at(i + 1)->setIsFoodInside(true);
                segments_.at(i)->setIsFoodInside(false);
            }
            else
            {
                segments_.at(i + 1)->setIsFoodInside(false);
            }
        }
    }
}

void Snake::processFoodEaten()
{
    segments_.front()->setIsFoodInside(true);
}

void Snake::grow(Direction tailDirection)
{
    const Coordinates& tailCoordinates = segments_.back()->getCoordinates();

    if(tailDirection == Direction::LEFT)
    {
        addSegment(tailCoordinates + std::pair{+1, 0});
    }
    else if(tailDirection == Direction::RIGHT)
    {
        addSegment(tailCoordinates + std::pair{-1, 0});
    }
    else if(tailDirection == Direction::UP)
    {
        addSegment(tailCoordinates + std::pair{0, -1});
    }
    else if(tailDirection == Direction::DOWN)
    {
        addSegment(tailCoordinates + std::pair{0, +1});
    }
}

void Snake::addSegment(const Coordinates& coordinates)
{
    segments_.emplace_back(std::make_unique<SnakeSegment>(coordinates));
}

Direction Snake::calculateSegmentDirection(const Coordinates& previousSegmentCoordinates, const Coordinates& currentSegmentCoordinates)
{
    const std::pair<int, int> coordinatesDifference = currentSegmentCoordinates - previousSegmentCoordinates;

    if(coordinatesDifference == std::pair{+1, 0})
    {
        return Direction::LEFT;
    }
    else if(coordinatesDifference == std::pair{-1, 0})
    {
        return Direction::RIGHT;
    }
    else if(coordinatesDifference == std::pair{0, +1})
    {
        return Direction::UP;
    }
    else if(coordinatesDifference == std::pair{0, -1})
    {
        return Direction::DOWN;
    }
    else
    {
        throw std::runtime_error("Wrong coordinates difference");
    }
}

std::vector<Coordinates> Snake::getAllSegmentsCoordinatesExceptForHead()
{
    std::vector<Coordinates> allSegmentsCoordinatesExceptForHead;

    for(int i = 1; i < segments_.size(); ++i)
    {
        allSegmentsCoordinatesExceptForHead.push_back(segments_.at(i)->getCoordinates());
    }

    return allSegmentsCoordinatesExceptForHead;
}

std::ostream& operator<<(std::ostream& os, const Snake& snake)
{
    for(const auto& segment : snake.segments_)
    {
        os << segment->getCoordinates();
    }

    return os;
}
