#pragma once

#include <QObject>

enum class Direction
{
    LEFT = 1, RIGHT = 2, UP = 3, DOWN = 4
};

class DirectionQml
{
    Q_GADGET

public:
    enum DirectionEnum
    {
        // map C++ enum to QML
        LEFT = static_cast<int>(Direction::LEFT),
        RIGHT = static_cast<int>(Direction::RIGHT),
        UP = static_cast<int>(Direction::UP),
        DOWN = static_cast<int>(Direction::DOWN)
    };

    Q_ENUM(DirectionEnum)
};
