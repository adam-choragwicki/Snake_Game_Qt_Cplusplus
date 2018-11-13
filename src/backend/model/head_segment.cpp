#include "head_segment.h"
#include <QPainter>
#include "spdlog/spdlog.h"

HeadSegment::HeadSegment(const Coordinates& coordinates, const Direction& movementDirection, AnimationManager* animationManager) : BodySegment(coordinates, movementDirection, animationManager)
{}

HeadSegment::~HeadSegment()
{
    //qDebug() << "Destroying head";
}

void HeadSegment::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(COLOR);

    painter->drawRoundedRect(rect_, RATIO_PERCENTAGE, RATIO_PERCENTAGE, Qt::RelativeSize);

    switch(movementDirection_)
    {
        case Direction::LEFT:
        case Direction::RIGHT:
            drawEyes(painter, 0, EYE_SOCKETS_SPACING);
            break;

        case Direction::UP:
        case Direction::DOWN:
            drawEyes(painter, EYE_SOCKETS_SPACING, 0);
            break;

        default:
            throw std::runtime_error("Error, cannot draw snake eyes, wrong direction");
    }
}

void HeadSegment::drawEyes(QPainter* painter, int eyeXOffset, int eyeYOffset)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(EYE_SOCKET_COLOR);

    const QPoint center = rect_.toRect().center();

    const int eye1X = center.x() + eyeXOffset - HALF_EYE_SOCKET_SIZE;
    const int eye1Y = center.y() + eyeYOffset - HALF_EYE_SOCKET_SIZE;

    const int eye2X = center.x() - eyeXOffset - HALF_EYE_SOCKET_SIZE;
    const int eye2Y = center.y() - eyeYOffset - HALF_EYE_SOCKET_SIZE;

    drawEyeSockets(painter, eye1X, eye1Y, eye2X, eye2Y);
    drawPupils(painter, eye1X, eye1Y, eye2X, eye2Y);
}

void HeadSegment::drawEyeSockets(QPainter* painter, const int eye1X, const int eye1Y, const int eye2X, const int eye2Y)
{
    painter->drawEllipse(eye1X, eye1Y, EYE_SOCKET_SIZE, EYE_SOCKET_SIZE);
    painter->drawEllipse(eye2X, eye2Y, EYE_SOCKET_SIZE, EYE_SOCKET_SIZE);
}

void HeadSegment::drawPupils(QPainter* painter, const int eye1X, const int eye1Y, const int eye2X, const int eye2Y)
{
    painter->setBrush(PUPIL_COLOR);

    updatePupilPosition();

    const int pupil1X = eye1X + HALF_EYE_SOCKET_SIZE + pupilOffset_.x() - HALF_PUPIL_SIZE;
    const int pupil1Y = eye1Y + HALF_EYE_SOCKET_SIZE + pupilOffset_.y() - HALF_PUPIL_SIZE;

    const int pupil2X = eye2X + HALF_EYE_SOCKET_SIZE + pupilOffset_.x() - HALF_PUPIL_SIZE;
    const int pupil2Y = eye2Y + HALF_EYE_SOCKET_SIZE + pupilOffset_.y() - HALF_PUPIL_SIZE;

    painter->drawEllipse(pupil1X, pupil1Y, PUPIL_SIZE, PUPIL_SIZE);
    painter->drawEllipse(pupil2X, pupil2Y, PUPIL_SIZE, PUPIL_SIZE);
}

void HeadSegment::updatePupilPosition()
{
    /*Calculate the vector from the snake's head to the food*/
    const QPointF headCenter = sceneBoundingRect().center();
    const QPointF directionToFood = pupilSightTargetPosition_ - headCenter;

    const double angle = std::atan2(directionToFood.y(), directionToFood.x());
    const int maxOffset = HALF_EYE_SOCKET_SIZE - HALF_PUPIL_SIZE;

    pupilOffset_.setX(static_cast<int>(std::cos(angle) * maxOffset));
    pupilOffset_.setY(static_cast<int>(std::sin(angle) * maxOffset));
}

void HeadSegment::setNewPupilSightTargetPosition(const QPointF& pupilSightTargetPosition)
{
    pupilSightTargetPosition_ = pupilSightTargetPosition;
}
