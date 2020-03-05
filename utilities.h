#pragma once

int const SQUARE_SIZE = 30;
int const ROWS_COUNT = 25;
int const COLUMNS_COUNT = 50;

/*Do not modify beyond this point*/
int const WALL_THICKNESS = SQUARE_SIZE;
int const MINIMUM_ROW_COLUMN = 0;
int const MAXIMUM_ROW = ROWS_COUNT - 1;
int const MAXIMUM_COLUMN = COLUMNS_COUNT - 1;

int const LEFT_BORDER_X = SQUARE_SIZE/2;
int const RIGHT_BORDER_X = COLUMNS_COUNT * SQUARE_SIZE + 2 * WALL_THICKNESS;
int const RIGHT_BORDER_X_OFFSET = -SQUARE_SIZE/2;
int const TOP_Y = SQUARE_SIZE/2;
int const BOTTOM_Y = ROWS_COUNT * SQUARE_SIZE + 2 * WALL_THICKNESS;
int const BOTTOM_Y_OFFSET = -SQUARE_SIZE/2;

int const GAME_TICK = 100;

enum class Direction
{
    left = 1,
    up = 2,
    down = 3,
    right = 4
};
