#pragma once

#include <QInternal>

namespace Config
{
    namespace Arena
    {
        const int MIN_ROW_COLUMN = 1;
        const int COLUMNS_COUNT = 40;
        const int ROWS_COUNT = 20;
        const int MAX_ROW = ROWS_COUNT;
        const int MAX_COLUMN = COLUMNS_COUNT;
    }

    namespace Speed
    {
        const int DEFAULT_SPEED_LEVEL = 5;
        const int MIN_SPEED_LEVEL = 1;
        const int MAX_SPEED_LEVEL = 10;
    }

    namespace Key
    {
        const Qt::Key BOOST_KEY = Qt::Key_Space;
    }
}
