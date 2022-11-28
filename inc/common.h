#pragma once

enum class Direction
{
    LEFT = 1, RIGHT = 2, UP = 3, DOWN = 4
};

enum class Key
{
    LEFT, RIGHT, UP, DOWN, PLUS, MINUS, SPACE
};

enum class GameState
{
    RUNNING, STOPPED, PAUSED
};

enum class GameResult
{
    WIN, LOSE
};
