#include "inc/food.h"
#include "inc/drawer.h"
#include "inc/common.h"

Food::Food()
{
    foodSquareGraphicalRectItem_ = nullptr;
}

void Food::generateAndPlace()
{
    foodSquareGraphicalRectItem_ = nullptr;

    int positionX = randomGenerator_.bounded(gameArenaParameters::MINIMUM_ROW_COLUMN, gameArenaParameters::MAXIMUM_COLUMN);
    int positionY = randomGenerator_.bounded(gameArenaParameters::MINIMUM_ROW_COLUMN, gameArenaParameters::MAXIMUM_ROW);

    position_.setX(positionX);
    position_.setY(positionY);

    foodSquareGraphicalRectItem_ = Drawer::drawFood(position_);
}
