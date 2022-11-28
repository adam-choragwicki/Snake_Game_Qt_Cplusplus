#pragma once

#include "config.h"

#include <QColor>

namespace GuiConfig
{
    namespace GameArenaParameters
    {
        const Qt::GlobalColor WALL_COLOR = Qt::white;

        const int BASIC_SQUARE_SIZE = 30;
        const int WALL_THICKNESS = BASIC_SQUARE_SIZE;
        const int LEFT_BORDER_X = BASIC_SQUARE_SIZE / 2;
        const int RIGHT_BORDER_X = Config::Arena::COLUMNS_COUNT * BASIC_SQUARE_SIZE + 2 * WALL_THICKNESS;
        const int RIGHT_BORDER_X_OFFSET = -BASIC_SQUARE_SIZE / 2;
        const int TOP_Y = BASIC_SQUARE_SIZE / 2;
        const int BOTTOM_Y = Config::Arena::ROWS_COUNT * BASIC_SQUARE_SIZE + 2 * WALL_THICKNESS;
        const int BOTTOM_Y_OFFSET = -BASIC_SQUARE_SIZE / 2;
    }

    namespace Food
    {
        const QColor FOOD_COLOR = Qt::red;
        const int FOOD_SIZE = 20;
        const int FOOD_OFFSET = 7;
        const int FOOD_INSIDE_SNAKE_SIZE = static_cast<int>(GameArenaParameters::BASIC_SQUARE_SIZE / 2);
        const int FOOD_INSIDE_SNAKE_OFFSET = 7;
        const QColor FOOD_INSIDE_SNAKE_COLOR = FOOD_COLOR;
    }

    namespace Snake
    {
        const int SNAKE_SEGMENT_SIZE = GameArenaParameters::BASIC_SQUARE_SIZE;
        const int SNAKE_EYE_SIZE = 6;
        const QColor SNAKE_HEAD_COLOR = Qt::yellow;
        const QColor SNAKE_BODY_COLOR = Qt::blue;
        const QColor SNAKE_EYES_COLOR = Qt::darkGreen;
    }
}
