#pragma once

#include <QColor>

namespace GameParameters
{
    const int basicSquareSize = 30;

    const int foodSize = 20;
    const int foodInsideSnakeSize = static_cast<int>(basicSquareSize / 2);
    const int foodInsideSnakeOffset = 7;
    const int snakeSegmentSize = basicSquareSize;
    const int snakeEyeSize = 6;

    inline static const QColor foodColor = Qt::red;
    inline static const QColor snakeHeadColor = Qt::yellow;
    inline static const QColor snakeBodyColor = Qt::blue;
    inline static const QColor snakeEyesColor = Qt::darkGreen;
    inline static const QColor foodInsideSnakeColor = foodColor;

    namespace Arena
    {
        const int rowsCount = 20;
        const int columnCount = 40;
        const int wallThickness = basicSquareSize;
        const int minimumRowColumn = 1;
        const int maximumRow = rowsCount;
        const int maximumColumn = columnCount;
        const int leftBorderX = basicSquareSize / 2;
        const int rightBorderX = columnCount * basicSquareSize + 2 * wallThickness;
        const int rightBorderXOffset = -basicSquareSize / 2;
        const int topY = basicSquareSize / 2;
        const int bottomY = rowsCount * basicSquareSize + 2 * wallThickness;
        const int bottomYOffset = -basicSquareSize / 2;
    }
}
