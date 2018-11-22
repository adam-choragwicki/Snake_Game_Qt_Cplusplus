#ifndef FOOD_H
#define FOOD_H

#include <QObject>
#include <QRandomGenerator>
#include <QPoint>
#include <QDebug>

class Food
{
private:
    QRandomGenerator randomGenerator;
    QPoint position;

public:
    Food();

    void generateAndPlace();
    void setPosition(QPoint pos) {position = pos;}
    QPoint getPosition() {return position;}
};

#endif // FOOD_H
