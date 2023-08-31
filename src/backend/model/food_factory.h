#pragma once

#include "food.h"
#include "snake.h"

class FoodFactory
{
public:
    explicit FoodFactory(Snake& snake);
    std::unique_ptr<Food> createFood();
    Coordinates generateNewFoodCoordinates(const std::vector<Coordinates>& availableCoordinates);

private:
    Snake& snake_;
    const std::vector<Coordinates> ALL_AVAILABLE_COORDINATES;
    std::vector<Coordinates> generateAllAvailableCoordinates();
};
