#include "food_manager.h"

FoodManager::FoodManager(Snake& snake)
{
    foodFactory_ = std::make_unique<FoodFactory>(snake);
}

void FoodManager::createFood()
{
    food_ = std::move(foodFactory_->createFood());
}

void FoodManager::removeFood()
{
    food_.reset();
}

bool FoodManager::foodExists() const
{
    return food_ != nullptr;
}

const Food& FoodManager::getFood() const
{
    return *food_;
}
