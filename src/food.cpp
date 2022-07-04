#include "food.h"
#include "drawer.h"
#include "config.h"

#include <QRandomGenerator>

Food::Food() : coordinates_(generateCoordinates())
{
    setPen(Qt::NoPen);
    setBrush(GameParameters::foodColor);

    setRect(coordinates_.x_ * GameParameters::snakeSegmentSize + GameParameters::foodInsideSnakeOffset,
            coordinates_.y_ * GameParameters::snakeSegmentSize + GameParameters::foodInsideSnakeOffset,
            GameParameters::foodSize,
            GameParameters::foodSize);

    Drawer::drawItem(this);
}

Food::~Food()
{
    Drawer::eraseItem(this);
}

Coordinates Food::generateCoordinates()
{
    int x = QRandomGenerator::global()->bounded(GameParameters::Arena::minimumRowColumn, GameParameters::Arena::maximumColumn);
    int y = QRandomGenerator::global()->bounded(GameParameters::Arena::minimumRowColumn, GameParameters::Arena::maximumRow);

    return Coordinates{x, y};
}
