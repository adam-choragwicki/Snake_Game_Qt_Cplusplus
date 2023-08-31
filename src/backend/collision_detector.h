#pragma once

#include "model/snake.h"
#include "model/food.h"

class CollisionDetector
{
public:
    static bool checkSnakeCollisionWithWall(const Snake& snake);
    static bool checkSnakeCollisionWithItself(const Snake& snake);
    static bool checkSnakeCollisionWithFood(const Snake& snake, const Food& food);

private:
    static bool checkSnakeCollisionWithLeftWall(const Snake& snake);
    static bool checkSnakeCollisionWithRightWall(const Snake& snake);
    static bool checkSnakeCollisionWithTopWall(const Snake& snake);
    static bool checkSnakeCollisionWithBottomWall(const Snake& snake);
};
