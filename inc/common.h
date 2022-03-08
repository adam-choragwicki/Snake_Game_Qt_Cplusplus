#pragma once

namespace GameArenaParameters
{
    const int snakeSegmentSize = 30;
    const int foodSize = 20;
    const int foodOffset = 5;
    const int rowsCount = 25;
    const int columnCount = 50;

/*Do not modify beyond this point*/
    const int wallThickness = snakeSegmentSize;
    const int minimumRowColumn = 0;
    const int maximumRow = rowsCount - 1;
    const int maxim = columnCount - 1;

    const int leftBorderX = snakeSegmentSize / 2;
    const int rightBorderX = columnCount * snakeSegmentSize + 2 * wallThickness;
    const int rightBorderXOffset = -snakeSegmentSize / 2;
    const int topY = snakeSegmentSize / 2;
    const int bottomY = rowsCount * snakeSegmentSize + 2 * wallThickness;
    const int bottomYOffset = -snakeSegmentSize / 2;
}
