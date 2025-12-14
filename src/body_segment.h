#pragma once

#include "direction.h"
#include "coordinates.h"
#include <QObject>

class BodySegment : public QObject
{
public:
    BodySegment(const Coordinates& coordinates, const Direction& movementDirection);
    ~BodySegment() override = default;

    bool operator==(const Coordinates& coordinates) const { return coordinates_ == coordinates; }

    [[nodiscard]] const Coordinates& getCoordinates() const { return coordinates_; }

    [[nodiscard]] Direction getMovementDirection() const { return movementDirection_; }

    void setMovementDirection(const Direction movementDirection) { movementDirection_ = movementDirection; }

    void setCoordinates(const Coordinates& coordinates) { coordinates_ = coordinates; }

protected:
    Direction movementDirection_;

private:
    Coordinates coordinates_;
};
