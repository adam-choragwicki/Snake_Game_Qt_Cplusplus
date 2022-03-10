#pragma once

namespace GameArenaParameters
{
    const int foodSize = 20;
    const int foodOffset = 5;
    const int rowsCount = 25;
    const int columnCount = 50;

    const int basicSquareSize = 30;
    const int snakeSegmentSize = basicSquareSize;
    const int wallThickness = basicSquareSize;
    const int minimumRowColumn = 0;
    const int maximumRow = rowsCount - 1;
    const int maximumColumn = columnCount - 1;

    const int leftBorderX = basicSquareSize / 2;
    const int rightBorderX = columnCount * basicSquareSize + 2 * wallThickness;
    const int rightBorderXOffset = -basicSquareSize / 2;
    const int topY = basicSquareSize / 2;
    const int bottomY = rowsCount * basicSquareSize + 2 * wallThickness;
    const int bottomYOffset = -basicSquareSize / 2;
}

enum class Direction
{
    left = 1,
    up = 2,
    down = 3,
    right = 4
};

enum class Key
{
    left,
    right,
    up,
    down,
    plus,
    minus,
    space
};
