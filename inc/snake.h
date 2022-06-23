#pragma once

#include "common.h"
#include "coordinates.h"

#include <QObject>
#include <QQueue>
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

    void updateHeadCoordinates()
    {
        headCoordinates_ = segments_.front().getCoordinates();
    }

    /*Forward declaration*/
    class Segment;

    QVector<Segment>& getSegments() {return segments_;}
    Coordinates& getHeadCoordinates() {return headCoordinates_;}
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
        explicit Segment(Coordinates coordinates)
        {
            coordinates_ = coordinates;
            isFoodInside_ = false;
        }

        Segment(int x, int y) : Segment(Coordinates{x, y})
        {}

        [[nodiscard]] bool isFoodInside() const {return isFoodInside_;}
        void setIsFoodInside(bool isFoodInside) {isFoodInside_ = isFoodInside;}
        bool operator==(const Coordinates& coordinates) const {return coordinates_ == coordinates;}
        [[nodiscard]] const Coordinates& getCoordinates() const {return coordinates_;}

    private:
        Coordinates coordinates_;
        bool isFoodInside_ {};
    };

private:
    Direction direction_ {};
    Direction nextDirection_ {};
    Coordinates headCoordinates_;
    QQueue<Segment> segments_;
    QVector<QGraphicsRectItem*> snakeSegmentsGraphicalRectItems_;
    QVector<QGraphicsEllipseItem*> foodInsideSnakeGraphicalEllipseItems_;
    QVector<QGraphicsEllipseItem*> snakeEyesGraphicalEllipseItems_;

    const QVector<Coordinates> startingCoordinates_ = {{20, 10}, {21, 10}, {22, 10}};

    void removeTail();
    void checkAndProcessGrowth();
};
