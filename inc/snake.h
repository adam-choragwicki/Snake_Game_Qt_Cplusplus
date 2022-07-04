#pragma once

#include "common.h"
#include "coordinates.h"
#include "snake_segment.h"

#include <QQueue>

class Snake
{
    friend std::ostream& operator<<(std::ostream& os, const Snake& snake);

public:
    Snake();
    ~Snake();

    void moveForward();
    void processFoodEaten();
    void grow(Direction tailDirection);

    void setDirection(const Direction& direction) {direction_ = direction;}
    void setNextDirection(const Direction& nextDirection) {nextDirection_ = nextDirection;}

    QVector<SnakeSegment*>& getSegments() {return segments_;}
    QVector<Coordinates> getAllSegmentsCoordinatesExceptForHead();
    [[nodiscard]] const Coordinates& getHeadCoordinates() const {return segments_.front()->getCoordinates();}
    [[nodiscard]] const Coordinates& getTailCoordinates() const {return segments_.back()->getCoordinates();}
    Direction& getDirection() {return direction_;}
    Direction& getNextDirection() {return nextDirection_;}

private:
    Direction direction_ {};
    Direction nextDirection_ {};
    QQueue<SnakeSegment*> segments_;

    const QVector<Coordinates> startingCoordinates_ = {{20, 10}, {21, 10}, {22, 10}};

    void addSegment(const Coordinates& coordinates);
    void shiftFoodInsideSnake(Direction& tailSegmentDirection);
    Direction calculateSegmentDirection(const Coordinates& previousSegmentCoordinates, const Coordinates& currentSegmentCoordinates);
};
