#pragma once

#include "direction.h"
#include "coordinates.h"
#include "custom_graphics_item.h"
#include <QObject>
#include <QPointF>
#include <QDebug>

class AnimationManager;
class QPropertyAnimation;

class BodySegment : public QObject, public CustomGraphicsItem
{
Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)

public:
    BodySegment(const Coordinates& coordinates, const Direction& movementDirection, AnimationManager* animationManager);
    ~BodySegment() override;

    void calculateAndSetNewCoordinatesAndDirection();

    bool operator==(const Coordinates& coordinates) const
    { return coordinates_ == coordinates; }

    [[nodiscard]] const Coordinates& getCoordinates() const
    { return coordinates_; }

    [[nodiscard]] Direction getMovementDirection() const
    { return movementDirection_; }

    void setMovementDirection(Direction movementDirection)
    { movementDirection_ = movementDirection; }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

protected:
    static const int RATIO_PERCENTAGE = 50;
    Direction movementDirection_;

private slots:
    void onAnimationFinished();

private:
    inline static const QColor COLOR{70, 116, 233};

    Coordinates coordinates_;

    Coordinates newCoordinatesAfterMovement_{0, 0};

    QPropertyAnimation* animation_{};
};
