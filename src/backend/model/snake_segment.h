#pragma once

#include "direction.h"
#include "coordinates.h"

class SnakeSegment
{
public:
    SnakeSegment(const Coordinates& coordinates, const Direction& movementDirection);
    virtual ~SnakeSegment() = default;

    void move();

    bool operator==(const Coordinates& coordinates) const
    { return coordinates_ == coordinates; }

    [[nodiscard]] const Coordinates& getCoordinates() const
    { return coordinates_; }

    [[nodiscard]] Direction getMovementDirection() const
    { return movementDirection_; }

    void setMovementDirection(Direction movementDirection)
    { movementDirection_ = movementDirection; }

protected:
    Coordinates coordinates_;
    Direction movementDirection_;
};
