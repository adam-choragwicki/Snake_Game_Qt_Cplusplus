#pragma once

#include "common.h"
#include "coordinates.h"

#include <QObject>
#include <QQueue>
#include <QGraphicsRectItem>
#include <QPainter>

class SnakeSegment : public QGraphicsRectItem
{
public:
    explicit SnakeSegment(Coordinates coordinates) :
            QGraphicsRectItem(coordinates.x * GameParameters::snakeSegmentSize + GameParameters::snakeSegmentSize,
                              coordinates.y * GameParameters::snakeSegmentSize + GameParameters::snakeSegmentSize,
                              GameParameters::snakeSegmentSize,
                              GameParameters::snakeSegmentSize), coordinates_(coordinates)
    {
        isFoodInside_ = false;

        setPen(Qt::NoPen);
        setBrush(GameParameters::snakeBodyColor);
        show();
    }

    SnakeSegment(int x, int y) : SnakeSegment(Coordinates{x, y})
    {}

    [[nodiscard]] bool isFoodInside() const {return isFoodInside_;}
    void setIsFoodInside(bool isFoodInside) {isFoodInside_ = isFoodInside;}
    bool operator==(const Coordinates& coordinates) const {return coordinates_ == coordinates;}
    [[nodiscard]] const Coordinates& getCoordinates() const {return coordinates_;}

private:
    Coordinates coordinates_;
    bool isFoodInside_ {};
};

class Snake
{
public:
    Snake();
    ~Snake();

    void moveForward();
    void processFoodEaten();
    void grow();

    void setDirection(const Direction& direction) {direction_ = direction;}
    void setNextDirection(const Direction& nextDirection) {nextDirection_ = nextDirection;}

    QVector<SnakeSegment*>& getSegments() {return segments_;}
    [[nodiscard]] const Coordinates& getHeadCoordinates() const {return segments_.front()->getCoordinates();}
    Direction& getDirection() {return direction_;}
    Direction& getNextDirection() {return nextDirection_;}
    QVector<QGraphicsRectItem*>& getSnakeSegmentsGraphicalRectItems() {return snakeSegmentsGraphicalRectItems_;}
    QVector<QGraphicsEllipseItem*>& getFoodInsideSnakeGraphicalEllipseItem() {return foodInsideSnakeGraphicalEllipseItems_;}
    QVector<QGraphicsEllipseItem*>& getSnakeEyesGraphicalEllipseItem() {return snakeEyesGraphicalEllipseItems_;}

private:
    Direction direction_ {};
    Direction nextDirection_ {};
    QQueue<SnakeSegment*> segments_;
    QVector<QGraphicsRectItem*> snakeSegmentsGraphicalRectItems_;
    QVector<QGraphicsEllipseItem*> foodInsideSnakeGraphicalEllipseItems_;
    QVector<QGraphicsEllipseItem*> snakeEyesGraphicalEllipseItems_;

    const QVector<Coordinates> startingCoordinates_ = {{20, 10}, {21, 10}, {22, 10}};

    void removeTail();
    void checkAndProcessGrowth();
};
