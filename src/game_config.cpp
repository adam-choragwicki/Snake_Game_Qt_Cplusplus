#include "game_config.h"

GameConfig::GameConfig()
{
    // Arena configuration
    arenaConfig_.BASE_SQUARE_SIZE = 40;

    arenaConfig_.ROW_COUNT = 20;
    arenaConfig_.COLUMN_COUNT = 20;

    arenaConfig_.TOTAL_ROW_COUNT_INCLUDING_BOUNDARY_WALLS = arenaConfig_.ROW_COUNT + 2;
    arenaConfig_.TOTAL_COLUMN_COUNT_INCLUDING_BOUNDARY_WALLS = arenaConfig_.COLUMN_COUNT + 2;

    arenaConfig_.MINIMUM_X = 1;
    arenaConfig_.MINIMUM_Y = 1;

    arenaConfig_.MAXIMUM_X = arenaConfig_.COLUMN_COUNT;
    arenaConfig_.MAXIMUM_Y = arenaConfig_.ROW_COUNT;

    arenaConfig_.TOTAL_FIELDS_COUNT = arenaConfig_.MAXIMUM_X * arenaConfig_.MAXIMUM_Y;

    // Snake configuration
    snakeConfig_.STARTING_HEAD_COORDINATES = {
        arenaConfig_.TOTAL_ROW_COUNT_INCLUDING_BOUNDARY_WALLS / 2,
        arenaConfig_.TOTAL_COLUMN_COUNT_INCLUDING_BOUNDARY_WALLS / 2
    };

    snakeConfig_.STARTING_DIRECTION = Direction::LEFT;
    snakeConfig_.STARTING_TOTAL_SEGMENT_COUNT = 5;

    this->SNAKE_MOVEMENT_INTERVAL_MS = 100;
}
