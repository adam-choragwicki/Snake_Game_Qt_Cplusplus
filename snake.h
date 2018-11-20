#ifndef SNAKE_H
#define SNAKE_H

#include <QObject>
#include <QVector>
#include <QPoint>
#include <QDebug>

class Snake
{
private:
    int size;
    int direction;
    int nextDirection;
    QPoint headPosition;
    QPoint tailPosition;
    QVector<QPoint> positions;
    bool isGrowing;

public:
    Snake();

    void move(int direction);
    bool isMovePossible();
    void grow();

    void setHeadPosition(QPoint headPoint);
    void setDirection(int dir);
    void setNextDirection(int nextdir);

    QVector<QPoint> getPositions() {return positions;}
    QPoint getHeadPosition() {return headPosition;}
    QPoint getTailPosition() {return tailPosition;}
    int getDirection() {return direction;}
    int getNextDirection() {return nextDirection;}

    enum direction {left = 1, up = 2, down = 3, right = 4};
};

#endif // SNAKE_H
