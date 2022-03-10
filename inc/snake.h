#pragma once

#include "drawer.h"
#include "common.h"

#include <QObject>
#include <QVector>
#include <QPoint>
#include <QGraphicsRectItem>

class Snake
{
public:
    Snake();
    void move();
    void grow();
    void reset();

    void setHeadPosition(const QPoint& headPosition) {headPosition_ = headPosition;}
    void setDirection(const Direction& direction) {direction_ = direction;}
    void setNextDirection(const Direction& nextDirection) {nextDirection_ = nextDirection;}

    QVector<QPoint>& getPositions() {return positions_;}
    QPoint& getHeadPosition() {return headPosition_;}
    Direction& getDirection() {return direction_;}
    Direction& getNextDirection() {return nextDirection_;}
    QVector<QGraphicsRectItem*>& getSnakeSquaresGraphicalRectItems() {return snakeSquaresGraphicalRectItems_;}

private:
    Direction direction_;
    Direction nextDirection_;
    QPoint headPosition_;
    QVector<QPoint> positions_;
    QVector<QGraphicsRectItem*> snakeSquaresGraphicalRectItems_;

    const QVector<QPoint> startingPositions_ = {QPoint(GameArenaParameters::columnCount / 2 + 2, GameArenaParameters::rowsCount / 2),
                                                QPoint(GameArenaParameters::columnCount / 2 + 1, GameArenaParameters::rowsCount / 2),
                                                QPoint(GameArenaParameters::columnCount / 2, GameArenaParameters::rowsCount / 2)};
};
