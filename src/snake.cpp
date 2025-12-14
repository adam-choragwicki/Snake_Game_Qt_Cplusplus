#include "snake.h"
#include "head_segment.h"
#include <QDebug>

Snake::Snake(const GameConfig& gameConfig, const Coordinates& startingHeadCoordinates, const Direction startingDirection,
             const int startingTotalSegmentsCount) : STARTING_HEAD_COORDINATES(startingHeadCoordinates), STARTING_DIRECTION(startingDirection), STARTING_TOTAL_SEGMENT_COUNT(startingTotalSegmentsCount)
{
    qDebug().noquote() << "Initializing snake of size" << startingTotalSegmentsCount << "and head at coordinates:" << startingHeadCoordinates.toString();

    segments_.reserve(gameConfig.arena().TOTAL_FIELDS_COUNT);

    nextHeadDirection_ = STARTING_DIRECTION;

    createHead();
    createSegments();

    emit stateChanged();
}

void Snake::reset()
{
    segments_.clear();

    nextHeadDirection_ = STARTING_DIRECTION;

    growFlag_ = false;

    createHead();
    createSegments();

    emit stateChanged();
}

void Snake::createHead()
{
    const auto& head = segments_.emplace_back(std::make_unique<HeadSegment>(STARTING_HEAD_COORDINATES, STARTING_DIRECTION));
    qDebug().noquote() << "Snake head created at coordinates:" << head->getCoordinates().toString();
}

void Snake::createSegments()
{
    while (segments_.size() != STARTING_TOTAL_SEGMENT_COUNT)
    {
        appendSegment();
    }

    emit stateChanged();
}

void Snake::moveForward()
{
    if (segments_.empty())
    {
        qFatal() << "Snake is empty, cannot move forward";
        return;
    }

    moveBodySegments();
    moveHead();

    emit stateChanged();
}

void Snake::moveBodySegments()
{
    // ==========================================================
    // MOVE ALL BODY SEGMENTS (except the head) TO THE POSITION OF THE SEGMENT IN FRONT OF THEM.
    //
    // Why backwards?
    // Because if we start from the head, we would overwrite positions before the next segment can copy them.
    // By going from tail to head, we keep all data correctly.
    //
    // Example for 4 segments: [H][1][2][3]
    //
    //   Step 1: segment 3 copies segment 2
    //   Step 2: segment 2 copies segment 1
    //   Step 3: segment 1 copies segment H
    //
    // After this loop, the body "follows" the head. Head movement will be applied afterwards.
    // ==========================================================

    // Loop backwards starting from the LAST segment (tail) and stop at index 1 (because index 0 = head, never copies anyone).
    for (size_t i = segments_.size() - 1; i > 0; --i)
    {
        // copy the coordinates of the segment in front of us. Example: segment 3 gets segment 2 coordinates.
        segments_[i]->setCoordinates(segments_[i - 1]->getCoordinates());

        // copy the movement direction, segments follow the direction of the segment before them
        segments_[i]->setMovementDirection(segments_[i - 1]->getMovementDirection());
    }
}

void Snake::moveHead()
{
    // ==========================================================
    // MOVE THE HEAD FORWARD
    // Only the head determines the new direction and performs the actual movement based on its direction.
    // All other segments already copied its previous position in the loop above.
    // ==========================================================
    auto& head = dynamic_cast<HeadSegment&>(*segments_.front());

    Coordinates newHeadCoordinates = head.getCoordinates();

    // compute new head coordinates from the current direction
    switch (head.getMovementDirection())
    {
        case Direction::UP: newHeadCoordinates.y_--;
            break;
        case Direction::DOWN: newHeadCoordinates.y_++;
            break;
        case Direction::LEFT: newHeadCoordinates.x_--;
            break;
        case Direction::RIGHT: newHeadCoordinates.x_++;
            break;
    }

    head.setCoordinates(newHeadCoordinates);
}

void Snake::appendSegment()
{
    if (segments_.empty())
    {
        throw std::runtime_error("Error, cannot append segment to 0-length snake");
    }

    const Coordinates tailCoordinates = getTailCoordinates();
    const Direction tailMovementDirection = getTail().getMovementDirection();

    Coordinates newSegmentCoordinates{0, 0};

    switch (tailMovementDirection)
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

    const auto& newSegment = segments_.emplace_back(std::make_unique<BodySegment>(newSegmentCoordinates, tailMovementDirection));
    qDebug().noquote() << "Snake segment appended at coordinates:" << newSegment->getCoordinates().toString();
}

void Snake::eatFood()
{
    if (!growFlag_)
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
    allSegmentsCoordinates.reserve(segments_.size());

    for (const auto& segment: segments_)
    {
        allSegmentsCoordinates.push_back(segment->getCoordinates());
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
    for (const auto& segment: snake.segments_)
    {
        os << segment->getCoordinates();
    }

    return os;
}

void Snake::setNextHeadDirection(const Direction& nextDirection)
{
    if (const Direction currentDirection = getMovementDirection(); currentDirection != nextDirection)
    {
        switch (nextDirection)
        {
            case Direction::LEFT:
                if (currentDirection != Direction::RIGHT)
                {
                    // qDebug() << "Setting new snake direction to LEFT";
                    nextHeadDirection_ = Direction::LEFT;
                }
                break;

            case Direction::RIGHT:
                if (currentDirection != Direction::LEFT)
                {
                    // qDebug() << "Setting new snake direction to RIGHT";
                    nextHeadDirection_ = Direction::RIGHT;
                }
                break;

            case Direction::UP:
                if (currentDirection != Direction::DOWN)
                {
                    // qDebug() << "Setting new snake direction to UP";
                    nextHeadDirection_ = Direction::UP;
                }
                break;

            case Direction::DOWN:
                if (currentDirection != Direction::UP)
                {
                    // qDebug() << "Setting new snake direction to DOWN";
                    nextHeadDirection_ = Direction::DOWN;
                }
                break;

            default:
                qWarning() << "Wrong direction";
        }
    }
    else
    {
        qWarning() << "Trying to set snake direction to the same as the current direction";
    }
}

void Snake::grow()
{
    if (growFlag_)
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

    for (const auto& segment: segments_)
    {
        string += segment->getCoordinates().toString();
    }

    return string;
}
