#pragma once

#include "common.h"
#include "coordinates.h"

class SnakeSegment
{
public:
    explicit SnakeSegment(const Coordinates& coordinates);
    ~SnakeSegment();

    Direction move(Direction direction);

    [[nodiscard]] bool isFoodInside() const {return isFoodInside_;}
    void setIsFoodInside(bool isFoodInside) {isFoodInside_ = isFoodInside;}
    bool operator==(const Coordinates& coordinates) const {return coordinates_ == coordinates;}
    [[nodiscard]] const Coordinates& getCoordinates() const {return coordinates_;}

protected:
    Coordinates coordinates_;
    bool isFoodInside_ {};
};

class HeadSegment : public SnakeSegment
{
public:
    explicit HeadSegment(const Coordinates& coordinates, Direction& direction);

private:
    Direction& direction_;
};
