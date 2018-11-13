#include <QEventLoop>
#include <QBrush>
#include <QPainter>
#include <QPropertyAnimation>
#include "body_segment.h"
#include "config_prod.h"
#include "animation_manager.h"

BodySegment::BodySegment(const Coordinates& coordinates, const Direction& movementDirection, AnimationManager* animationManager) :
        CustomGraphicsItem(QRectF(0, 0, ConfigProd::Arena::PRIMARY_SQUARE_SIZE, ConfigProd::Arena::PRIMARY_SQUARE_SIZE)), coordinates_(coordinates), movementDirection_(movementDirection)
{
    setPositionOnSceneAtCoordinates(coordinates_);

    if(animationManager)
    {
        //qDebug() << "Creating segment";
        animation_ = new QPropertyAnimation(this, "pos", this);
        animationManager->addAnimation(animation_);

        animation_->setDuration(4 * ConfigProd::MOVEMENT_DELAY_MS);

        connect(animation_, &QPropertyAnimation::finished, this, &BodySegment::onAnimationFinished);
    }
}

BodySegment::~BodySegment()
{
    //qDebug() << "Destroying segment";
}

void BodySegment::calculateAndSetNewCoordinatesAndDirection()
{
    std::pair<int, int> directionalOffset{};

    switch(movementDirection_)
    {
        case Direction::LEFT:
            directionalOffset = {-1, 0};
            break;

        case Direction::RIGHT:
            directionalOffset = {+1, 0};
            break;

        case Direction::UP:
            directionalOffset = {0, -1};
            break;

        case Direction::DOWN:
            directionalOffset = {0, +1};
            break;

        default:
            throw std::runtime_error("Wrong directional offset");
    }

    newCoordinatesAfterMovement_ = coordinates_ + directionalOffset;

    if(coordinates_ == newCoordinatesAfterMovement_)
    {
        qWarning("Warning, trying to animate from/to same coordinates");
        return;
    }

    const int rowDifference = newCoordinatesAfterMovement_.y_ - coordinates_.y_;
    const int columnDifference = newCoordinatesAfterMovement_.x_ - coordinates_.x_;

    const QPointF startPosition = pos();
    const QPointF destinationPosition = startPosition + QPointF(columnDifference * ConfigProd::Arena::PRIMARY_SQUARE_SIZE, rowDifference * ConfigProd::Arena::PRIMARY_SQUARE_SIZE);

    if(animation_)
    {
        animation_->setStartValue(startPosition);
        animation_->setEndValue(destinationPosition);
    }
    else
    {
        onAnimationFinished();
    }
}

void BodySegment::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    CustomGraphicsItem::paint(painter, option, widget);

    painter->setPen(Qt::NoPen);
    painter->setBrush(COLOR);

    painter->drawRoundedRect(rect_, RATIO_PERCENTAGE, RATIO_PERCENTAGE, Qt::RelativeSize);
}

void BodySegment::onAnimationFinished()
{
    coordinates_ = newCoordinatesAfterMovement_;
}
