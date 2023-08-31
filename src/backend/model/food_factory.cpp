#include "food_factory.h"
#include <QRandomGenerator>
#include <algorithm>

FoodFactory::FoodFactory(Snake& snake) : ALL_AVAILABLE_COORDINATES(generateAllAvailableCoordinates()), snake_(snake)
{}

std::unique_ptr<Food> FoodFactory::createFood()
{
    std::vector<Coordinates> allSnakeSegmentsCoordinates = snake_.getAllSegmentsCoordinates();
    std::sort(allSnakeSegmentsCoordinates.begin(), allSnakeSegmentsCoordinates.end());
    std::vector<Coordinates> currentlyAvailableCoordinates;

    std::set_difference(ALL_AVAILABLE_COORDINATES.begin(),
                        ALL_AVAILABLE_COORDINATES.end(),
                        allSnakeSegmentsCoordinates.begin(),
                        allSnakeSegmentsCoordinates.end(),
                        std::back_inserter(currentlyAvailableCoordinates));

    return std::make_unique<Food>(generateNewFoodCoordinates(currentlyAvailableCoordinates));
}

Coordinates FoodFactory::generateNewFoodCoordinates(const std::vector<Coordinates>& availableCoordinates)
{
    return availableCoordinates.at(QRandomGenerator::global()->bounded(static_cast<int>(availableCoordinates.size())));
}

std::vector<Coordinates> FoodFactory::generateAllAvailableCoordinates()
{
    std::vector<Coordinates> allAvailableCoordinates;

    for(int column = Config::Arena::MINIMUM_X; column <= Config::Arena::MAXIMUM_X; ++column)
    {
        for(int row = Config::Arena::MINIMUM_Y; row <= Config::Arena::MAXIMUM_Y; ++row)
        {
            allAvailableCoordinates.push_back({column, row});
        }
    }

    return allAvailableCoordinates;
}
