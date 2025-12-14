#pragma once

#include <QObject>
#include "coordinates.h"

class FoodManager;

class FoodModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int x READ getX NOTIFY positionChanged)
    Q_PROPERTY(int y READ getY NOTIFY positionChanged)

signals:
    void positionChanged();

public slots:
    void syncWithFoodManager();

public:
    explicit FoodModel(FoodManager& manager);

    int getX() const;
    int getY() const;

private:
    FoodManager& foodManager_;
};
