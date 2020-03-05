#include "food.h"

Food::Food()
{
    
}

void Food::GenerateAndPlace()
{
    int positionX, positionY;

    positionX = m_RandomGenerator.bounded(1,50);
    positionY = m_RandomGenerator.bounded(1,25);

    qDebug() << "Pozycja X: " << positionX;
    qDebug() << "Pozycja Y: " << positionY;

    m_Position.setX(positionX);
    m_Position.setY(positionY);
}
