#include "food.h"
#include "drawer.h"
#include "common.h"

#include <QRandomGenerator>

void Food::generate()
{
    if(foodSquareGraphicalEllipseItem_ == nullptr)
    {
        int positionX = QRandomGenerator::global()->bounded(GameParameters::Arena::minimumRowColumn, GameParameters::Arena::maximumColumn);
        int positionY = QRandomGenerator::global()->bounded(GameParameters::Arena::minimumRowColumn, GameParameters::Arena::maximumRow);

        position_.setX(positionX);
        position_.setY(positionY);
    }
    else
    {
        throw std::runtime_error("Another food item already exists");
    }
}
