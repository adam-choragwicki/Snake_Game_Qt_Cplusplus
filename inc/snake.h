#pragma once

#include "common.h"

#include <QObject>
#include <QVector>
#include <QPoint>
#include <QGraphicsRectItem>

class Segment
{
public:
    explicit Segment(QPoint coordinates)
    {
        coordinates_ = coordinates;
    }

    Segment(int x, int y) : Segment(QPoint(x, y))
    {}

    bool operator==(const QPoint& coordinates) const
    {
        return coordinates_ == coordinates;
    }

    [[nodiscard]] const QPoint& getCoordinates() const
    {
        return coordinates_;
    }

private:
    QPoint coordinates_;
};

class Snake
{
public:
    Snake();
    void move();
    void grow();
    void reset();

    void setDirection(const Direction& direction) {direction_ = direction;}
    void setNextDirection(const Direction& nextDirection) {nextDirection_ = nextDirection;}

    void updateHeadPosition()
    {
        headPosition_ = segments_.at(0).getCoordinates();
    }

    QVector<Segment>& getSegments() {return segments_;}
    QPoint& getHeadPosition() {return headPosition_;}
    Direction& getDirection() {return direction_;}
    Direction& getNextDirection() {return nextDirection_;}
    QVector<QGraphicsRectItem*>& getSnakeSquaresGraphicalRectItems() {return snakeSquaresGraphicalRectItems_;}

    inline static const QColor headColor = Qt::yellow;
    inline static const QColor bodyColor = Qt::green;

private:
    Direction direction_ {};
    Direction nextDirection_ {};
    QPoint headPosition_;
    QVector<Segment> segments_;
    QVector<QGraphicsRectItem*> snakeSquaresGraphicalRectItems_;

    const QVector<QPoint> startingPositions_ = {QPoint(20, 10),
                                                QPoint(21, 10),
                                                QPoint(22, 10)};
};
