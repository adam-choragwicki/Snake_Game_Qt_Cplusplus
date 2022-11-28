#include "food.h"
#include "config.h"

#include <QRandomGenerator>

Food::Food() : coordinates_(generateCoordinates())
{

}

Coordinates Food::generateCoordinates()
{
    const int x = QRandomGenerator::global()->bounded(Config::Arena::MIN_ROW_COLUMN, Config::Arena::MAX_COLUMN);
    const int y = QRandomGenerator::global()->bounded(Config::Arena::MIN_ROW_COLUMN, Config::Arena::MAX_ROW);

    return Coordinates{x, y};
}
