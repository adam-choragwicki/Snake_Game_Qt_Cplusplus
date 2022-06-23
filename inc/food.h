#pragma once

#include "coordinates.h"

#include <QObject>
#include <QGraphicsEllipseItem>

class Food
{
public:
    Food() = default;

    void generate();
    [[nodiscard]] const Coordinates& getPosition() const {return coordinates_;}
    [[nodiscard]] QGraphicsEllipseItem*& getFoodGraphicalEllipseItem(){return foodSquareGraphicalEllipseItem_;}

    inline static const QColor color = Qt::red;

private:
    Coordinates coordinates_;
    QGraphicsEllipseItem* foodSquareGraphicalEllipseItem_ {};
};
