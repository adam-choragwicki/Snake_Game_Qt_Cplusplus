#pragma once

#include "coordinates.h"

class Food
{
public:
    explicit Food(const Coordinates& coordinates);

    [[nodiscard]] const Coordinates& getCoordinates() const
    { return coordinates_; }

private:
    const Coordinates coordinates_;
};
