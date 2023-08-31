#pragma once

#include "speed_level.h"
#include <QInternal>
#include <chrono>
#include <map>

namespace Config
{
    namespace Arena
    {
        const int MINIMUM_X = 1;
        const int MINIMUM_Y = 1;
        const int MAXIMUM_X = 40;
        const int MAXIMUM_Y = 20;
        constexpr int TOTAL_FIELDS_COUNT = MAXIMUM_Y * MAXIMUM_X;
    }

    namespace Speed
    {
        const int DEFAULT_SPEED_LEVEL = 5;
        const int MIN_SPEED_LEVEL = 1;
        const int MAX_SPEED_LEVEL = 10;

        using namespace std::chrono_literals;

        const std::map<SpeedLevel, std::chrono::duration<int, std::milli>> SPEED_LEVEL_TO_TIMER_INTERVAL_MAP{{SpeedLevel(1),  250ms},
                                                                                                             {SpeedLevel(2),  230ms},
                                                                                                             {SpeedLevel(3),  210ms},
                                                                                                             {SpeedLevel(4),  190ms},
                                                                                                             {SpeedLevel(5),  170ms},
                                                                                                             {SpeedLevel(6),  150ms},
                                                                                                             {SpeedLevel(7),  130ms},
                                                                                                             {SpeedLevel(8),  110ms},
                                                                                                             {SpeedLevel(9),  90ms},
                                                                                                             {SpeedLevel(10), 70ms}};

        const std::chrono::duration<int, std::milli> SPEED_BOOST_TIMER_INTERVAL = 30ms;
    }

    namespace Key
    {
        const Qt::Key BOOST_KEY = Qt::Key_Space;
    }
}
