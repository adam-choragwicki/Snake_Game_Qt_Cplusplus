#include "food.h"

Food::Food()
{
    
}

void Food::generateAndPlace()
{
    int positionX, positionY;

    positionX = randomGenerator.bounded(1,50);
    positionY = randomGenerator.bounded(1,25);

    qDebug() << "Pozycja X: " << positionX;
    qDebug() << "Pozycja Y: " << positionY;

    position.setX(positionX);
    position.setY(positionY);
}
