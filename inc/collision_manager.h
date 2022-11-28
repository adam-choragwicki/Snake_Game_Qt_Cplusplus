#pragma once

#include "snake.h"
#include "food.h"

namespace CollisionManager
{
    bool checkSnakeCollisionWithWall(Snake* snake);
    bool checkSnakeCollisionWithItself(Snake* snake);
    bool checkSnakeCollisionWithFoodSquare(Snake* snake, Food* food);
};
