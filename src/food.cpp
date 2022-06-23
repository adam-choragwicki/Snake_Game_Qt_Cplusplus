#include "food.h"
#include "drawer.h"
#include "common.h"

#include <QRandomGenerator>

Food::Food() : coordinates_(generateCoordinates())
{
    Drawer::drawFood(*this);
}

Food::~Food()
{
    Drawer::eraseFood(*this);
}

Coordinates Food::generateCoordinates()
{
    int x = QRandomGenerator::global()->bounded(GameParameters::Arena::minimumRowColumn, GameParameters::Arena::maximumColumn);
    int y = QRandomGenerator::global()->bounded(GameParameters::Arena::minimumRowColumn, GameParameters::Arena::maximumRow);

    return Coordinates{x, y};
}

void Food::setFoodSquareGraphicalEllipseItem(QGraphicsEllipseItem* foodSquareGraphicalEllipseItem)
{
    if(foodSquareGraphicalEllipseItem_ == nullptr)
    {
        foodSquareGraphicalEllipseItem_ = foodSquareGraphicalEllipseItem;
    }
    else
    {
        throw std::runtime_error("Food ellipse item already exists");
    }
}
