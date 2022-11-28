#include "collision_manager.h"
#include "config.h"

bool CollisionManager::checkSnakeCollisionWithWall(Snake* snake)
{
    const Coordinates& headCoordinates = snake->getHeadCoordinates();
    const Direction direction = snake->getDirection();

    if(direction == Direction::LEFT && headCoordinates.x_ == Config::Arena::MIN_ROW_COLUMN)
    {
        return true;
    }
    else if(direction == Direction::RIGHT && headCoordinates.x_ == Config::Arena::MAX_COLUMN)
    {
        return true;
    }
    else if(direction == Direction::UP && headCoordinates.y_ == Config::Arena::MIN_ROW_COLUMN)
    {
        return true;
    }
    else if(direction == Direction::DOWN && headCoordinates.y_ == Config::Arena::MAX_ROW)
    {
        return true;
    }

    return false;
}

bool CollisionManager::checkSnakeCollisionWithItself(Snake* snake)
{
    const Coordinates& headCoordinates = snake->getHeadCoordinates();
    const Direction direction = snake->getDirection();
    const auto allSegmentsCoordinatesExceptForHead = snake->getAllSegmentsCoordinatesExceptForHead();

    auto contains = [&allSegmentsCoordinatesExceptForHead](const Coordinates& coordinates)
    {
        return std::ranges::find(allSegmentsCoordinatesExceptForHead, coordinates) != allSegmentsCoordinatesExceptForHead.end();
    };

    if(direction == Direction::LEFT && contains(headCoordinates + std::pair{-1, 0}))
    {
        return true;
    }
    else if(direction == Direction::RIGHT && contains(headCoordinates + std::pair{+1, 0}))
    {
        return true;
    }
    else if(direction == Direction::UP && contains(headCoordinates + std::pair{0, -1}))
    {
        return true;
    }
    else if(direction == Direction::DOWN && contains(headCoordinates + std::pair{0, +1}))
    {
        return true;
    }

    return false;
}

bool CollisionManager::checkSnakeCollisionWithFoodSquare(Snake* snake, Food* food)
{
    return snake->getHeadCoordinates() == food->getCoordinates();
}
