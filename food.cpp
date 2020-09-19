#include "food.h"
#include "drawer.h"

Food::Food()
{
    m_pFoodSquareGraphicalRectItem = nullptr;
}

void Food::GenerateAndPlace()
{
    m_pFoodSquareGraphicalRectItem = nullptr;

    int positionX = m_RandomGenerator.bounded(Drawer::MINIMUM_ROW_COLUMN, Drawer::MAXIMUM_COLUMN);
    int positionY = m_RandomGenerator.bounded(Drawer::MINIMUM_ROW_COLUMN, Drawer::MAXIMUM_ROW);

    m_Position.setX(positionX);
    m_Position.setY(positionY);

    m_pFoodSquareGraphicalRectItem = Drawer::DrawFood(m_Position);
}
