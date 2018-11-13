#pragma once

#include "food.h"
#include "food_factory.h"
#include <memory>

class FoodManager
{
public:
    explicit FoodManager(Snake& snake);
    void reset();

    void createFood();
    void createFood(const Coordinates& coordinates);

    void respawnFood();

    [[nodiscard]] bool foodExists() const;
    [[nodiscard]] Food& getFood();

private:
    std::unique_ptr<FoodFactory> foodFactory_;
    std::unique_ptr<Food> food_;
};
