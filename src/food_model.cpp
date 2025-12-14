#include "food_model.h"
#include "food_manager.h"
#include <QDebug>

FoodModel::FoodModel(FoodManager& manager) : QObject(nullptr), foodManager_(manager)
{
    connect(&foodManager_, &FoodManager::foodMoved, this, &FoodModel::syncWithFoodManager);
    syncWithFoodManager();
}

int FoodModel::getX() const
{
    return foodManager_.getFoodCoordinates().x_;
}

int FoodModel::getY() const
{
    return foodManager_.getFoodCoordinates().y_;
}

void FoodModel::syncWithFoodManager()
{
    qDebug() << "syncWithFoodManager";

    emit positionChanged();
}
