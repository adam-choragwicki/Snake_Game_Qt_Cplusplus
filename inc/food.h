#pragma once

#include "coordinates.h"

class Food
{
public:
    Food();

    [[nodiscard]] const Coordinates& getCoordinates() const
    { return coordinates_; }

private:
    Coordinates generateCoordinates();

    const Coordinates coordinates_;
};
