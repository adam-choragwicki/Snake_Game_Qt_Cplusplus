#include "collision_manager.h"
#include "model/arena.h"
#include "model/snake.h"
#include "model/food.h"

bool CollisionManager::checkSnakeCollisionWithItself(const Snake& snake)
{
    const auto allSegmentsCoordinatesExceptForHead = snake.getAllSegmentsCoordinatesExceptForHead();

    auto contains = [&allSegmentsCoordinatesExceptForHead](const Coordinates& coordinates)
    {
        return std::ranges::find(allSegmentsCoordinatesExceptForHead, coordinates) != allSegmentsCoordinatesExceptForHead.end();
    };

    std::pair<int, int> coordinatesOffset;

    switch(snake.getMovementDirection())
    {
        case Direction::LEFT:
            coordinatesOffset = std::pair{-1, 0};
            break;

        case Direction::RIGHT:
            coordinatesOffset = std::pair{+1, 0};
            break;

        case Direction::UP:
            coordinatesOffset = std::pair{0, -1};
            break;

        case Direction::DOWN:
            coordinatesOffset = std::pair{0, +1};
            break;
    }

    Coordinates projectedNextHeadCoordinates(snake.getHeadCoordinates() + coordinatesOffset);
    return contains(projectedNextHeadCoordinates);
}

bool CollisionManager::checkSnakeCollisionWithFood(const Snake& snake, const Food& food)
{
    return snake.getHeadCoordinates() == food.getCoordinates();
}

bool CollisionManager::checkSnakeCollisionWithArenaBoundary(const Snake& snake, const Arena& arena)
{
    return checkSnakeCollisionWithLeftWall(snake, arena) || checkSnakeCollisionWithRightWall(snake, arena) || checkSnakeCollisionWithTopWall(snake, arena) || checkSnakeCollisionWithBottomWall(snake, arena);
}

bool CollisionManager::checkSnakeCollisionWithLeftWall(const Snake& snake, const Arena& arena)
{
    return snake.getMovementDirection() == Direction::LEFT && snake.getHeadCoordinates().x_ == arena.getMinimumX();
}

bool CollisionManager::checkSnakeCollisionWithRightWall(const Snake& snake, const Arena& arena)
{
    return snake.getMovementDirection() == Direction::RIGHT && snake.getHeadCoordinates().x_ == arena.getMaximumX();
}

bool CollisionManager::checkSnakeCollisionWithTopWall(const Snake& snake, const Arena& arena)
{
    return snake.getMovementDirection() == Direction::UP && snake.getHeadCoordinates().y_ == arena.getMinimumY();
}

bool CollisionManager::checkSnakeCollisionWithBottomWall(const Snake& snake, const Arena& arena)
{
    return snake.getMovementDirection() == Direction::DOWN && snake.getHeadCoordinates().y_ == arena.getMaximumY();
}
