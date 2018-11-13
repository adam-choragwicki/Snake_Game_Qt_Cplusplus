#pragma once

#include "direction.h"
#include "coordinates.h"

namespace GenericTestConfig
{
    struct Snake
    {
        const Direction STARTING_DIRECTION = Direction::LEFT;
        const Coordinates STARTING_HEAD_COORDINATES{10, 10};
        const int STARTING_TOTAL_SEGMENT_COUNT = 3;
    };
}
