#include "collision_detector.h"
#include "config.h"

bool CollisionDetector::checkSnakeCollisionWithItself(const Snake& snake)
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

bool CollisionDetector::checkSnakeCollisionWithFood(const Snake& snake, const Food& food)
{
    return snake.getHeadCoordinates() == food.getCoordinates();
}

bool CollisionDetector::checkSnakeCollisionWithWall(const Snake& snake)
{
    return checkSnakeCollisionWithLeftWall(snake) || checkSnakeCollisionWithRightWall(snake) || checkSnakeCollisionWithTopWall(snake) || checkSnakeCollisionWithBottomWall(snake);
}

bool CollisionDetector::checkSnakeCollisionWithLeftWall(const Snake& snake)
{
    return snake.getMovementDirection() == Direction::LEFT && snake.getHeadCoordinates().x_ == Config::Arena::MINIMUM_X;
}

bool CollisionDetector::checkSnakeCollisionWithRightWall(const Snake& snake)
{
    return snake.getMovementDirection() == Direction::RIGHT && snake.getHeadCoordinates().x_ == Config::Arena::MAXIMUM_X;
}

bool CollisionDetector::checkSnakeCollisionWithTopWall(const Snake& snake)
{
    return snake.getMovementDirection() == Direction::UP && snake.getHeadCoordinates().y_ == Config::Arena::MINIMUM_Y;
}

bool CollisionDetector::checkSnakeCollisionWithBottomWall(const Snake& snake)
{
    return snake.getMovementDirection() == Direction::DOWN && snake.getHeadCoordinates().y_ == Config::Arena::MAXIMUM_Y;
}
