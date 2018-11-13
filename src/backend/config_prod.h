#pragma once

#include <QInternal>
#include <chrono>
#include "direction.h"
#include "coordinates.h"

namespace ConfigProd
{
    namespace Arena
    {
        const int PRIMARY_SQUARE_SIZE = 40;

        const int PLAYABLE_HORIZONTAL_SQUARES_COUNT = 20;
        const int PLAYABLE_VERTICAL_SQUARES_COUNT = 20;

        const int TOTAL_HORIZONTAL_SQUARES_COUNT_INCLUDING_BOUNDARY_WALLS = PLAYABLE_HORIZONTAL_SQUARES_COUNT + 2;
        const int TOTAL_VERTICAL_SQUARES_COUNT_INCLUDING_BOUNDARY_WALLS = PLAYABLE_VERTICAL_SQUARES_COUNT + 2;

        const int MINIMUM_X = 1;
        const int MINIMUM_Y = 1;
        const int MAXIMUM_X = PLAYABLE_HORIZONTAL_SQUARES_COUNT;
        const int MAXIMUM_Y = PLAYABLE_VERTICAL_SQUARES_COUNT;

        constexpr int TOTAL_FIELDS_COUNT = MAXIMUM_Y * MAXIMUM_X;
    }

    struct Snake
    {
        const Coordinates STARTING_HEAD_COORDINATES{ConfigProd::Arena::TOTAL_HORIZONTAL_SQUARES_COUNT_INCLUDING_BOUNDARY_WALLS / 2, ConfigProd::Arena::TOTAL_VERTICAL_SQUARES_COUNT_INCLUDING_BOUNDARY_WALLS / 2};
        const Direction STARTING_DIRECTION = Direction::LEFT;

        const int STARTING_TOTAL_SEGMENT_COUNT = 5;
    };

    extern int MOVEMENT_DELAY_MS;
}
