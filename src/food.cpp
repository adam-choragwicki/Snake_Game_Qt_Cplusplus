#include "food.h"
#include "drawer.h"
#include "common.h"

#include <QRandomGenerator>

void Food::generate()
{
    if(foodSquareGraphicalEllipseItem_ == nullptr)
    {
        int x = QRandomGenerator::global()->bounded(GameParameters::Arena::minimumRowColumn, GameParameters::Arena::maximumColumn);
        int y = QRandomGenerator::global()->bounded(GameParameters::Arena::minimumRowColumn, GameParameters::Arena::maximumRow);

        coordinates_ = Coordinates{x, y};
    }
    else
    {
        throw std::runtime_error("Another food item already exists");
    }
}
