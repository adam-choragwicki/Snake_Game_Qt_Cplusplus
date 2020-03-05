#include "food.h"
#include "utilities.h"

Food::Food()
{
    
}

void Food::GenerateAndPlace()
{
    int positionX, positionY;

    positionX = m_RandomGenerator.bounded(MINIMUM_ROW_COLUMN, MAXIMUM_COLUMN);
    positionY = m_RandomGenerator.bounded(MINIMUM_ROW_COLUMN, MAXIMUM_ROW);

    qDebug() << "Food position X: " << positionX;
    qDebug() << "Food position Y: " << positionY;

    m_Position.setX(positionX);
    m_Position.setY(positionY);
}
