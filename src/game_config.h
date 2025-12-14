#pragma once

#include "direction.h"
#include "coordinates.h"

class GameConfig
{
public:
    GameConfig();

    struct ArenaConfig
    {
        int BASE_SQUARE_SIZE; // logical size of each tile, snake segment, etc.

        int ROW_COUNT;
        int COLUMN_COUNT;

        int TOTAL_ROW_COUNT_INCLUDING_BOUNDARY_WALLS;
        int TOTAL_COLUMN_COUNT_INCLUDING_BOUNDARY_WALLS;

        int MINIMUM_X;
        int MINIMUM_Y;

        int MAXIMUM_X;
        int MAXIMUM_Y;

        int TOTAL_FIELDS_COUNT;
    };

    struct SnakeConfig
    {
        Coordinates STARTING_HEAD_COORDINATES{0, 0};
        Direction STARTING_DIRECTION = Direction::LEFT;
        int STARTING_TOTAL_SEGMENT_COUNT = 5;
    };

    int SNAKE_MOVEMENT_INTERVAL_MS{};

    [[nodiscard]] const ArenaConfig& arena() const { return arenaConfig_; }
    [[nodiscard]] const SnakeConfig& snake() const { return snakeConfig_; }

private:
    ArenaConfig arenaConfig_;
    SnakeConfig snakeConfig_;
};
