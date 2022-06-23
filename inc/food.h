#pragma once

#include "coordinates.h"

#include <QObject>
#include <QGraphicsEllipseItem>

class Food
{
public:
    Food();
    virtual ~Food();

    [[nodiscard]] const Coordinates& getPosition() const {return coordinates_;}
    [[nodiscard]] QGraphicsEllipseItem* getFoodGraphicalEllipseItem(){return foodSquareGraphicalEllipseItem_;}
    void setFoodSquareGraphicalEllipseItem(QGraphicsEllipseItem* foodSquareGraphicalEllipseItem);
    void resetFoodSquareGraphicalEllipseItem() {foodSquareGraphicalEllipseItem_ = nullptr;}

    inline static const QColor color = Qt::red;

private:
    const Coordinates coordinates_;
    QGraphicsEllipseItem* foodSquareGraphicalEllipseItem_ {};

    Coordinates generateCoordinates();
};
