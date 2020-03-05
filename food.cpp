#include "food.h"
#include "utilities.h"
#include "drawer.h"

Food::Food()
{
    m_pFoodSquareGraphicalRectItem = nullptr;
}

void Food::GenerateAndPlace()
{
    m_pFoodSquareGraphicalRectItem = nullptr;

    int positionX = m_RandomGenerator.bounded(MINIMUM_ROW_COLUMN, MAXIMUM_COLUMN);
    int positionY = m_RandomGenerator.bounded(MINIMUM_ROW_COLUMN, MAXIMUM_ROW);

    m_Position.setX(positionX);
    m_Position.setY(positionY);

    m_pFoodSquareGraphicalRectItem = Drawer::DrawFood(m_Position);
}
