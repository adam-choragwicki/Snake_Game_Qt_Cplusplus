#pragma once

namespace GameParameters
{
    const int basicSquareSize = 30;

    const int foodSize = 20;
    const int foodInsideSnakeSize = static_cast<int>(basicSquareSize / 2);
    const int foodInsideSnakeOffset = 7;
    const int snakeSegmentSize = basicSquareSize;
    const int snakeEyeSize = 6;

    namespace Arena
    {
        const int rowsCount = 20;
        const int columnCount = 40;
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
}

enum class Direction
{
    left = 0,
    right = 1,
    up = 2,
    down = 3
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
