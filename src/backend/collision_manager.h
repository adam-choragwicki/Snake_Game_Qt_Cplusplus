#pragma once

class Arena;
class Snake;
class Food;

class CollisionManager
{
public:
    static bool checkSnakeCollisionWithArenaBoundary(const Snake& snake, const Arena& arena);
    static bool checkSnakeCollisionWithItself(const Snake& snake);
    static bool checkSnakeCollisionWithFood(const Snake& snake, const Food& food);

private:
    static bool checkSnakeCollisionWithLeftWall(const Snake& snake, const Arena& arena);
    static bool checkSnakeCollisionWithRightWall(const Snake& snake, const Arena& arena);
    static bool checkSnakeCollisionWithTopWall(const Snake& snake, const Arena& arena);
    static bool checkSnakeCollisionWithBottomWall(const Snake& snake, const Arena& arena);
};
