#pragma once

#include "coordinates.h"
#include "food_factory.h"
#include <QObject>

class Snake;

class FoodManager : public QObject
{
    Q_OBJECT

signals:
    void foodMoved();

public:
    FoodManager(const GameConfig& config, const Snake& snake);

    [[nodiscard]] Coordinates getFoodCoordinates() const { return foodCoordinates_; }

    void spawnFoodAtCoordinates(const Coordinates& coordinates);
    void spawnFoodAtRandomCoordinates();

private:
    FoodFactory foodFactory_;
    Coordinates foodCoordinates_{0, 0};
};
