#include "food.h"
#include "drawer.h"
#include "common.h"

Food::Food()
{
    foodSquareGraphicalEllipseItem_ = nullptr;
}

void Food::generateAndPlace()
{
    foodSquareGraphicalEllipseItem_ = nullptr;

    int positionX = randomGenerator_.bounded(GameArenaParameters::minimumRowColumn, GameArenaParameters::maxim);
    int positionY = randomGenerator_.bounded(GameArenaParameters::minimumRowColumn, GameArenaParameters::maximumRow);

    position_.setX(positionX);
    position_.setY(positionY);

    foodSquareGraphicalEllipseItem_ = Drawer::drawFood(position_);
}
