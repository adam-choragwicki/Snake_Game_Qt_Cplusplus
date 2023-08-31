#pragma once

#include "config.h"
#include <QColor>

namespace GuiConfig
{
    namespace GameArena
    {
        namespace Field
        {
            const int SIZE = 30;
        }

        namespace Edge
        {
            constexpr QColor COLOR(160, 54, 35);
        }
    }

    namespace Food
    {
        const QColor COLOR = Qt::red;
        const int SIZE = 20;
        const int OFFSET = 5;
    }

    namespace Snake
    {
        const int SEGMENT_SIZE = GameArena::Field::SIZE;
        const int ROUNDED_RECT_RATIO_PERCENTAGE = 50;
        const int EYE_SIZE = 6;
        const QColor HEAD_COLOR = Qt::yellow;
        const QColor BODY_COLOR = Qt::blue;
        const QColor EYES_COLOR = Qt::darkGreen;
    }
}
