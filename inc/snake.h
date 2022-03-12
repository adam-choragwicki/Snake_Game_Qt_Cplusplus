#pragma once

#include "common.h"

#include <QObject>
#include <QQueue>
#include <QPoint>
#include <QGraphicsRectItem>
#include <QPainter>

class Snake
{
public:
    Snake();

    void move();
    void processFoodEaten();
    void grow();
    void reset();

    void setDirection(const Direction& direction) {direction_ = direction;}
    void setNextDirection(const Direction& nextDirection) {nextDirection_ = nextDirection;}

    void updateHeadPosition()
    {
        headPosition_ = segments_.front().getCoordinates();
    }

    /*Forward declaration*/
    class Segment;

    QVector<Segment>& getSegments() {return segments_;}
    QPoint& getHeadPosition() {return headPosition_;}
    Direction& getDirection() {return direction_;}
    Direction& getNextDirection() {return nextDirection_;}
    QVector<QGraphicsRectItem*>& getSnakeSegmentsGraphicalRectItems() {return snakeSegmentsGraphicalRectItems_;}
    QVector<QGraphicsEllipseItem*>& getFoodInsideSnakeGraphicalEllipseItem() {return foodInsideSnakeGraphicalEllipseItems_;}
    QVector<QGraphicsEllipseItem*>& getSnakeEyesGraphicalEllipseItem() {return snakeEyesGraphicalEllipseItems_;}

    inline static const QColor headColor = Qt::yellow;
    inline static const QColor bodyColor = Qt::blue;
    inline static const QColor eyesColor = Qt::darkGreen;

    class Segment
    {
    public:
        explicit Segment(QPoint coordinates)
        {
            coordinates_ = coordinates;
            isFoodInside_ = false;
        }

        Segment(int x, int y) : Segment(QPoint(x, y))
        {}

        [[nodiscard]] bool isFoodInside() const {return isFoodInside_;}
        void setIsFoodInside(bool isFoodInside) {isFoodInside_ = isFoodInside;}
        bool operator==(const QPoint& coordinates) const {return coordinates_ == coordinates;}
        [[nodiscard]] const QPoint& getCoordinates() const {return coordinates_;}

    private:
        QPoint coordinates_;
        bool isFoodInside_ {};
    };

private:
    Direction direction_ {};
    Direction nextDirection_ {};
    QPoint headPosition_;
    QQueue<Segment> segments_;
    QVector<QGraphicsRectItem*> snakeSegmentsGraphicalRectItems_;
    QVector<QGraphicsEllipseItem*> foodInsideSnakeGraphicalEllipseItems_;
    QVector<QGraphicsEllipseItem*> snakeEyesGraphicalEllipseItems_;

    const QVector<QPoint> startingPositions_ = {QPoint(20, 10),
                                                QPoint(21, 10),
                                                QPoint(22, 10)};
    void removeTail();
    void checkAndProcessGrowth();
};
