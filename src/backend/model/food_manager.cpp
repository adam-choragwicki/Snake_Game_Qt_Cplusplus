#include "food_manager.h"

FoodManager::FoodManager(Snake& snake)
{
    foodFactory_ = std::make_unique<FoodFactory>(snake);
}

void FoodManager::reset()
{
    respawnFood();
}

void FoodManager::createFood()
{
    food_ = foodFactory_->createFoodAtRandomCoordinates();
}

void FoodManager::createFood(const Coordinates& coordinates)
{
    food_ = foodFactory_->createFoodAtGivenCoordinates(coordinates);
}

void FoodManager::respawnFood()
{
    food_->moveToNewCoordinates(foodFactory_->generateNewFoodCoordinates());
}

bool FoodManager::foodExists() const
{
    return food_ != nullptr;
}

Food& FoodManager::getFood()
{
    return *food_;
}
