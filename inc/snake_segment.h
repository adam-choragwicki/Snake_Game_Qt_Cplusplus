#pragma once

#include "common.h"
#include "coordinates.h"

#include <QGraphicsItem>
#include <QPen>
#include <QPainter>

class SnakeSegment : public QGraphicsItem
{
public:
    explicit SnakeSegment(const Coordinates& coordinates);
    ~SnakeSegment() override;

    Direction move(Direction direction);

    [[nodiscard]] bool isFoodInside() const {return isFoodInside_;}
    void setIsFoodInside(bool isFoodInside) {isFoodInside_ = isFoodInside;}
    bool operator==(const Coordinates& coordinates) const {return coordinates_ == coordinates;}
    [[nodiscard]] const Coordinates& getCoordinates() const {return coordinates_;}

protected:
    [[nodiscard]] QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    Coordinates coordinates_;
    bool isFoodInside_ {};
};

class HeadSegment : public SnakeSegment
{
public:
    explicit HeadSegment(const Coordinates& coordinates, Direction& direction);

private:
    [[nodiscard]] QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    Direction& direction_;
};
