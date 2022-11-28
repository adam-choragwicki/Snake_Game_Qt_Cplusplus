#pragma once

#include "common.h"
#include "coordinates.h"
#include "snake_segment.h"
#include <vector>
#include <deque>
#include "log_manager.h"

#include <QObject>

class Snake : public QObject
{
Q_OBJECT

    friend std::ostream& operator<<(std::ostream& os, const Snake& snake);

signals:
    void positionChangedEvent();

public:
    Snake();
    ~Snake() override = default;

    void moveForward();
    void processFoodEaten();
    void grow(Direction tailDirection);

    void setDirection(const Direction& direction)
    {
        direction_ = direction;
    }

    void setNextDirection(const Direction& nextDirection)
    {
        switch(nextDirection)
        {
            case Direction::LEFT:
                if(direction_ != Direction::RIGHT)
                {
                    nextDirection_ = Direction::LEFT;
                }
                break;

            case Direction::RIGHT:
                if(direction_ != Direction::LEFT)
                {
                    nextDirection_ = Direction::RIGHT;
                }
                break;

            case Direction::UP:
                if(direction_ != Direction::DOWN)
                {
                    nextDirection_ = Direction::UP;
                }
                break;

            case Direction::DOWN:
                if(direction_ != Direction::UP)
                {
                    nextDirection_ = Direction::DOWN;
                }
        }
    }

    std::deque<std::unique_ptr<SnakeSegment>>& getSegments()
    {
        return segments_;
    }

    std::vector<Coordinates> getAllSegmentsCoordinatesExceptForHead();

    [[nodiscard]] const Coordinates& getHeadCoordinates() const
    { return segments_.front()->getCoordinates(); }

    [[nodiscard]] const Coordinates& getTailCoordinates() const
    { return segments_.back()->getCoordinates(); }

    Direction& getDirection()
    { return direction_; }

    Direction& getNextDirection()
    { return nextDirection_; }

private:
    Direction direction_{};
    Direction nextDirection_{};

    std::deque<std::unique_ptr<SnakeSegment>> segments_;

    const std::vector<Coordinates> startingCoordinates_ = {{20, 10},
                                                           {21, 10},
                                                           {22, 10}};

    void addSegment(const Coordinates& coordinates);
    void shiftFoodInsideSnake(Direction& tailSegmentDirection);
    Direction calculateSegmentDirection(const Coordinates& previousSegmentCoordinates, const Coordinates& currentSegmentCoordinates);
};
