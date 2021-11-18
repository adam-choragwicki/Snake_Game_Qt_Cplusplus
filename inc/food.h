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
    void GenerateAndPlace();
    void SetPosition(QPoint position){m_Position = position;}
    QPoint& GetPosition() {return m_Position;}
    QGraphicsRectItem* GetFoodSquareGraphicalRectItem(){return m_pFoodSquareGraphicalRectItem;}

private:
    QRandomGenerator m_RandomGenerator;
    QPoint m_Position;

    QGraphicsRectItem* m_pFoodSquareGraphicalRectItem;
};
