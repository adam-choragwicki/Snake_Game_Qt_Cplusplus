#pragma once

#include "food.h"
#include "snake.h"

class FoodFactory
{
public:
    explicit FoodFactory(Snake& snake);
    std::unique_ptr<Food> createFoodAtRandomCoordinates();
    std::unique_ptr<Food> createFoodAtGivenCoordinates(const Coordinates& coordinates);
    Coordinates generateNewFoodCoordinates();

private:
    Snake& snake_;
    const std::vector<Coordinates> ALL_AVAILABLE_COORDINATES;
    std::vector<Coordinates> generateAllAvailableCoordinates();
};
