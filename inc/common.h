#pragma once

namespace gameArenaParameters{
const int SQUARE_SIZE = 30;
const int ROWS_COUNT = 25;
const int COLUMNS_COUNT = 50;

/*Do not modify beyond this point*/
const int WALL_THICKNESS = SQUARE_SIZE;
const int MINIMUM_ROW_COLUMN = 0;
const int MAXIMUM_ROW = ROWS_COUNT - 1;
const int MAXIMUM_COLUMN = COLUMNS_COUNT - 1;

const int LEFT_BORDER_X = SQUARE_SIZE/2;
const int RIGHT_BORDER_X = COLUMNS_COUNT * SQUARE_SIZE + 2 * WALL_THICKNESS;
const int RIGHT_BORDER_X_OFFSET = -SQUARE_SIZE/2;
const int TOP_Y = SQUARE_SIZE/2;
const int BOTTOM_Y = ROWS_COUNT * SQUARE_SIZE + 2 * WALL_THICKNESS;
const int BOTTOM_Y_OFFSET = -SQUARE_SIZE/2;
}
