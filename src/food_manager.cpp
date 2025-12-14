#include "food_manager.h"
#include "snake.h"
#include <QDebug>

FoodManager::FoodManager(const GameConfig& config, const Snake& snake) : QObject(nullptr), foodFactory_(config, snake)
{}

void FoodManager::spawnFoodAtCoordinates(const Coordinates& coordinates)
{
    qDebug().noquote() << "Spawning food at coordinates" << coordinates.toString();

    foodCoordinates_ = coordinates;
    emit foodMoved();
}

void FoodManager::spawnFoodAtRandomCoordinates()
{
    foodCoordinates_ = foodFactory_.generateNewCoordinates();

    qDebug().noquote() << "Spawning food at random coordinates" << foodCoordinates_.toString();

    emit foodMoved();
}
