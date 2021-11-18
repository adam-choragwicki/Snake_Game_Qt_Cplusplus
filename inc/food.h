#pragma once

#include <QObject>
#include <QRandomGenerator>
#include <QPoint>
#include <QDebug>
#include <QGraphicsRectItem>

class Food
{
public:
    Food();
    void generateAndPlace();
    void setPosition(QPoint position){position_ = position;}
    QPoint& getPosition() {return position_;}
    QGraphicsRectItem* getFoodSquareGraphicalRectItem(){return foodSquareGraphicalRectItem_;}

private:
    QRandomGenerator randomGenerator_;
    QPoint position_;
    QGraphicsRectItem* foodSquareGraphicalRectItem_;
};
