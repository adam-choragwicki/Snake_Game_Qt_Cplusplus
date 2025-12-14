#include "food_factory.h"
#include "snake.h"
#include <QRandomGenerator>
#include <algorithm>

FoodFactory::FoodFactory(const GameConfig& config, const Snake& snake) : config_(config), snake_(snake), allCoordinates_(generateAllTiles())
{}

std::vector<Coordinates> FoodFactory::generateAllTiles() const
{
    std::vector<Coordinates> result;

    for (int x = config_.arena().MINIMUM_X; x <= config_.arena().MAXIMUM_X; ++x)
    {
        for (int y = config_.arena().MINIMUM_Y; y <= config_.arena().MAXIMUM_Y; ++y)
        {
            result.push_back({x, y});
        }
    }

    return result;
}

Coordinates FoodFactory::generateNewCoordinates() const
{
    auto snakeCoords = snake_.getAllSegmentsCoordinates();
    std::sort(snakeCoords.begin(), snakeCoords.end());

    std::vector<Coordinates> freeTiles;
    std::set_difference(
        allCoordinates_.begin(), allCoordinates_.end(),
        snakeCoords.begin(), snakeCoords.end(),
        std::back_inserter(freeTiles)
    );

    int index = QRandomGenerator::global()->bounded(static_cast<int>(freeTiles.size()));
    return freeTiles[index];
}
