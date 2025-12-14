#pragma once

#include "coordinates.h"

class Arena;
class Snake;
class Food;

class CollisionManager
{
public:
    static bool checkSnakeCollisionWithArenaBoundary(const Snake& snake, const Arena& arena);
    static bool checkSnakeCollisionWithItself(const Snake& snake);
    static bool checkSnakeCollisionWithFood(const Snake& snake, const Coordinates& foodCoordinates);

private:
    static bool checkSnakeCollisionWithArenaLeftBoundary(const Snake& snake, const Arena& arena);
    static bool checkSnakeCollisionWithArenaRightBoundary(const Snake& snake, const Arena& arena);
    static bool checkSnakeCollisionWithArenaTopBoundary(const Snake& snake, const Arena& arena);
    static bool checkSnakeCollisionWithArenaBottomBoundary(const Snake& snake, const Arena& arena);
};
