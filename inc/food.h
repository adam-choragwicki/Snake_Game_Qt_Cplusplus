#pragma once

#include "coordinates.h"

#include <QGraphicsEllipseItem>

class Food : public QGraphicsEllipseItem
{
public:
    Food();
    ~Food() override;

    [[nodiscard]] const Coordinates& getPosition() const {return coordinates_;}

private:
    const Coordinates coordinates_;

    Coordinates generateCoordinates();
};
