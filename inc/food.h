#pragma once

#include <QObject>
#include <QRandomGenerator>
#include <QPoint>
#include <QGraphicsEllipseItem>

class Food
{
public:
    Food();
    void generateAndPlace();
    QPoint& getPosition() {return position_;}
    QGraphicsEllipseItem* getFoodSquareGraphicalEllipseItem(){return foodSquareGraphicalEllipseItem_;}

private:
    QRandomGenerator randomGenerator_;
    QPoint position_;
    QGraphicsEllipseItem* foodSquareGraphicalEllipseItem_;
};
