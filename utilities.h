#pragma once

int const SQUARE_SIZE = 30;
int const ROWS_COUNT = 25;
int const COLUMNS_COUNT = 50;

int const MINIMUM_ROW_COLUMN = 0;
int const MAXIMUM_ROW = 24;
int const MAXIMUM_COLUMN = 49;

int const LEFT_BORDER_X = 15;
int const RIGHT_BORDER_X = 1560;
int const RIGHT_BORDER_X_OFFSET = -15;
int const TOP_Y = 15;
int const BOTTOM_Y = 810;
int const BOTTOM_Y_OFFSET = -15;
int const WALL_THICKNESS = 30;

int const GAME_TICK = 100;

enum class Direction
{
    left = 1,
    up = 2,
    down = 3,
    right = 4
};
