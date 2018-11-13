#include <QEventLoop>
#include "snake.h"
#include "snake_reverse_iterator.h"
#include "head_segment.h"
#include <QCoreApplication>

Snake::Snake(const Coordinates& startingHeadCoordinates, const Direction startingDirection, const int startingTotalSegmentsCount, AnimationManager* animationManager) :
        STARTING_HEAD_COORDINATES(startingHeadCoordinates), STARTING_DIRECTION(startingDirection), STARTING_TOTAL_SEGMENT_COUNT(startingTotalSegmentsCount), animationManager_(animationManager)
{
    segments_.reserve(ConfigProd::Arena::TOTAL_FIELDS_COUNT);

    nextHeadDirection_ = STARTING_DIRECTION;

    createHead();
    createSegments();
}

void Snake::reset()
{
    animationManager_->reset();
    segments_.clear();

    nextHeadDirection_ = STARTING_DIRECTION;

    createHead();
    createSegments();
}

void Snake::createHead()
{
    auto& head = segments_.emplace_back(std::make_unique<HeadSegment>(STARTING_HEAD_COORDINATES, STARTING_DIRECTION, animationManager_));
    emit segmentAdded(*head);
}

void Snake::createSegments()
{
    while(segments_.size() != STARTING_TOTAL_SEGMENT_COUNT)
    {
        appendSegment();
    }
}

void Snake::moveForward()
{
    if(growFlag_)
    {
        throw std::runtime_error("Snake cannot move forward when grow flag is active");
    }

    for(SnakeReverseIterator snakeReverseIterator = createReverseIterator(); !snakeReverseIterator.isDone(); snakeReverseIterator.advance())
    {
        BodySegment& segment = snakeReverseIterator.current();

        segment.calculateAndSetNewCoordinatesAndDirection();

        if(snakeReverseIterator.hasNext())
        {
            const BodySegment& nextSegment = snakeReverseIterator.next();
            segment.setMovementDirection(nextSegment.getMovementDirection());
        }
    }

    if(animationManager_)
    {
        animationManager_->animateSegmentsToNewCoordinates();
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

    Coordinates newSegmentCoordinates{0, 0};

    switch(tailMovementDirection)
    {
        case Direction::LEFT:
            newSegmentCoordinates = tailCoordinates + std::pair{+1, 0};
            break;

        case Direction::RIGHT:
            newSegmentCoordinates = tailCoordinates + std::pair{-1, 0};
            break;

        case Direction::UP:
            newSegmentCoordinates = tailCoordinates + std::pair{0, +1};
            break;

        case Direction::DOWN:
            newSegmentCoordinates = tailCoordinates + std::pair{0, -1};
            break;
    }

    auto& newSegment = segments_.emplace_back(std::make_unique<BodySegment>(newSegmentCoordinates, tailMovementDirection, animationManager_));
    emit segmentAdded(*newSegment);
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

std::vector<Coordinates> Snake::getAllSegmentsCoordinates() const
{
    std::vector<Coordinates> allSegmentsCoordinates;

    for(const auto& segment : segments_)
    {
        allSegmentsCoordinates.push_back((*segment).getCoordinates());
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
        os << (*segment).getCoordinates();
    }

    return os;
}

void Snake::setNextHeadDirection(const Direction& nextDirection)
{
    Direction currentDirection = getMovementDirection();

    if(currentDirection != nextDirection)
    {
        switch(nextDirection)
        {
            case Direction::LEFT:
                if(currentDirection != Direction::RIGHT)
                {
                    nextHeadDirection_ = Direction::LEFT;
                }
                break;

            case Direction::RIGHT:
                if(currentDirection != Direction::LEFT)
                {
                    nextHeadDirection_ = Direction::RIGHT;
                }
                break;

            case Direction::UP:
                if(currentDirection != Direction::DOWN)
                {
                    nextHeadDirection_ = Direction::UP;
                }
                break;

            case Direction::DOWN:
                if(currentDirection != Direction::UP)
                {
                    nextHeadDirection_ = Direction::DOWN;
                }
        }
    }
}

SnakeReverseIterator Snake::createReverseIterator()
{
    return SnakeReverseIterator(segments_);
}

void Snake::grow()
{
    if(growFlag_)
    {
        appendSegment();
        growFlag_ = false;
    }
}

bool Snake::isNewMovementDirectionRequested()
{
    return getHead().getMovementDirection() != nextHeadDirection_;
}

void Snake::updateMovementDirection()
{
    getHead().setMovementDirection(nextHeadDirection_);
}

void Snake::setNewFoodPosition(const QPointF& foodPosition)
{
    getHead().setNewPupilSightTargetPosition(foodPosition);
}

const HeadSegment& Snake::getHead() const
{
    return dynamic_cast<HeadSegment&>(*segments_.front());
}

HeadSegment& Snake::getHead()
{
    return dynamic_cast<HeadSegment&>(*segments_.front());
}

Coordinates Snake::getHeadCoordinates() const
{
    return getHead().getCoordinates();
}

Direction Snake::getMovementDirection() const
{
    return getHead().getMovementDirection();
}

QString Snake::toString() const
{
    QString string;

    for(const auto& segment : segments_)
    {
        string += segment->getCoordinates().toString();
    }

    return string;
}
