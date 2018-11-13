#pragma once

#include <QtWidgets/QGraphicsScene>
#include "config_prod.h"

class GraphicsScene : public QGraphicsScene
{
public:
    GraphicsScene();

private:
    static const int ARENA_WIDTH_PX = ConfigProd::Arena::TOTAL_HORIZONTAL_SQUARES_COUNT_INCLUDING_BOUNDARY_WALLS * ConfigProd::Arena::PRIMARY_SQUARE_SIZE;
    static const int ARENA_HEIGHT_PX = ConfigProd::Arena::TOTAL_VERTICAL_SQUARES_COUNT_INCLUDING_BOUNDARY_WALLS * ConfigProd::Arena::PRIMARY_SQUARE_SIZE;;
};
