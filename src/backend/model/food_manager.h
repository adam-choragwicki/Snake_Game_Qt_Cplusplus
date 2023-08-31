#pragma once

#include "food.h"
#include <memory>
#include "food_factory.h"

class FoodManager
{
public:
    explicit FoodManager(Snake& snake);
    void createFood();
    void removeFood();

    [[nodiscard]] bool foodExists() const;
    [[nodiscard]] const Food& getFood() const;

private:
    std::unique_ptr<FoodFactory> foodFactory_;
    std::unique_ptr<Food> food_;
};
