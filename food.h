#pragma once

#include <QObject>
#include <QRandomGenerator>
#include <QPoint>
#include <QDebug>

class Food
{
public:
    Food();

    void GenerateAndPlace();
    void SetPosition(QPoint position){m_Position = position;}
    QPoint& GetPosition() {return m_Position;}

private:
    QRandomGenerator m_RandomGenerator;
    QPoint m_Position;
};
