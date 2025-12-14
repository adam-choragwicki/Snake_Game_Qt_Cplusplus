#include "collision_manager.h"
#include "arena.h"
#include "snake.h"
#include <QDebug>

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

bool CollisionManager::checkSnakeCollisionWithFood(const Snake& snake, const Coordinates& foodCoordinates)
{
    return snake.getHeadCoordinates() == foodCoordinates;
}

bool CollisionManager::checkSnakeCollisionWithArenaBoundary(const Snake& snake, const Arena& arena)
{
    if (checkSnakeCollisionWithArenaLeftBoundary(snake, arena))
    {
        qInfo() << "Snake hit arena left boundary";
        return true;
    }

    if (checkSnakeCollisionWithArenaRightBoundary(snake, arena))
    {
        qInfo() << "Snake hit arena right boundary";
        return true;
    }

    if (checkSnakeCollisionWithArenaTopBoundary(snake, arena))
    {
        qInfo() << "Snake hit arena top boundary";
        return true;
    }

    if (checkSnakeCollisionWithArenaBottomBoundary(snake, arena))
    {
        qInfo() << "Snake hit arena bottom boundary";
        return true;
    }

    return false;
}

bool CollisionManager::checkSnakeCollisionWithArenaLeftBoundary(const Snake& snake, const Arena& arena)
{
    return snake.getMovementDirection() == Direction::LEFT && snake.getHeadCoordinates().x_ == arena.getMinimumX();
}

bool CollisionManager::checkSnakeCollisionWithArenaRightBoundary(const Snake& snake, const Arena& arena)
{
    return snake.getMovementDirection() == Direction::RIGHT && snake.getHeadCoordinates().x_ == arena.getMaximumX();
}

bool CollisionManager::checkSnakeCollisionWithArenaTopBoundary(const Snake& snake, const Arena& arena)
{
    return snake.getMovementDirection() == Direction::UP && snake.getHeadCoordinates().y_ == arena.getMinimumY();
}

bool CollisionManager::checkSnakeCollisionWithArenaBottomBoundary(const Snake& snake, const Arena& arena)
{
    return snake.getMovementDirection() == Direction::DOWN && snake.getHeadCoordinates().y_ == arena.getMaximumY();
}
