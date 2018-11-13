#include "food_factory.h"
#include <QRandomGenerator>
#include <algorithm>

FoodFactory::FoodFactory(Snake& snake) : ALL_AVAILABLE_COORDINATES(generateAllAvailableCoordinates()), snake_(snake)
{}

std::unique_ptr<Food> FoodFactory::createFoodAtRandomCoordinates()
{
    std::vector<Coordinates> allSnakeSegmentsCoordinates = snake_.getAllSegmentsCoordinates();
    std::sort(allSnakeSegmentsCoordinates.begin(), allSnakeSegmentsCoordinates.end());
    std::vector<Coordinates> currentlyAvailableCoordinates;

    std::set_difference(ALL_AVAILABLE_COORDINATES.begin(), ALL_AVAILABLE_COORDINATES.end(), allSnakeSegmentsCoordinates.begin(), allSnakeSegmentsCoordinates.end(), std::back_inserter(currentlyAvailableCoordinates));

    return std::make_unique<Food>(generateNewFoodCoordinates());
}

std::unique_ptr<Food> FoodFactory::createFoodAtGivenCoordinates(const Coordinates& coordinates)
{
    std::vector<Coordinates> allSnakeSegmentsCoordinates = snake_.getAllSegmentsCoordinates();
    std::sort(allSnakeSegmentsCoordinates.begin(), allSnakeSegmentsCoordinates.end());
    std::vector<Coordinates> currentlyAvailableCoordinates;

    std::set_difference(ALL_AVAILABLE_COORDINATES.begin(), ALL_AVAILABLE_COORDINATES.end(), allSnakeSegmentsCoordinates.begin(), allSnakeSegmentsCoordinates.end(), std::back_inserter(currentlyAvailableCoordinates));

    if(auto iter = std::find(currentlyAvailableCoordinates.begin(), currentlyAvailableCoordinates.end(), coordinates); iter != currentlyAvailableCoordinates.end())
    {
        return std::make_unique<Food>(coordinates);
    }
    else
    {
        throw std::runtime_error("Error, generating food on non-empty coordinates");
    }
}

Coordinates FoodFactory::generateNewFoodCoordinates()
{
    std::vector<Coordinates> allSnakeSegmentsCoordinates = snake_.getAllSegmentsCoordinates();
    std::sort(allSnakeSegmentsCoordinates.begin(), allSnakeSegmentsCoordinates.end());
    std::vector<Coordinates> currentlyAvailableCoordinates;

    std::set_difference(ALL_AVAILABLE_COORDINATES.begin(), ALL_AVAILABLE_COORDINATES.end(), allSnakeSegmentsCoordinates.begin(), allSnakeSegmentsCoordinates.end(), std::back_inserter(currentlyAvailableCoordinates));

    return currentlyAvailableCoordinates.at(QRandomGenerator::global()->bounded(static_cast<int>(currentlyAvailableCoordinates.size())));
}

std::vector<Coordinates> FoodFactory::generateAllAvailableCoordinates()
{
    std::vector<Coordinates> allAvailableCoordinates;

    for(int column = ConfigProd::Arena::MINIMUM_X; column <= ConfigProd::Arena::MAXIMUM_X; ++column)
    {
        for(int row = ConfigProd::Arena::MINIMUM_Y; row <= ConfigProd::Arena::MAXIMUM_Y; ++row)
        {
            allAvailableCoordinates.push_back({column, row});
        }
    }

    return allAvailableCoordinates;
}
