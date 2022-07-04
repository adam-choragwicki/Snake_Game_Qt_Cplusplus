#include "snake_segment.h"
#include "log_manager.h"
#include "drawer.h"
#include "config.h"

SnakeSegment::SnakeSegment(const Coordinates& coordinates) : coordinates_(coordinates)
{
    Drawer::drawItem(this);
}

SnakeSegment::~SnakeSegment()
{
    Drawer::eraseItem(this);
}

QRectF SnakeSegment::boundingRect() const
{
    const int offsetX_ = 0;
    const int offsetY_ = 0;

    return QRect(coordinates_.x_ + offsetX_,
                 coordinates_.y_ + offsetY_,
                 GameParameters::snakeSegmentSize,
                 GameParameters::snakeSegmentSize);
}

void SnakeSegment::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    const int offsetX_ = 0;
    const int offsetY_ = 0;

    painter->setBrush(GameParameters::snakeBodyColor);
    painter->setPen(Qt::NoPen);
    painter->drawRect(coordinates_.x_ * GameParameters::snakeSegmentSize + offsetX_,
                      coordinates_.y_ * GameParameters::snakeSegmentSize + offsetY_,
                      GameParameters::snakeSegmentSize,
                      GameParameters::snakeSegmentSize);

    if(isFoodInside_)
    {
        painter->setBrush(GameParameters::foodInsideSnakeColor);
        painter->drawEllipse(coordinates_.x_ * GameParameters::snakeSegmentSize + offsetX_ + GameParameters::foodInsideSnakeOffset,
                             coordinates_.y_ * GameParameters::snakeSegmentSize + offsetY_ + GameParameters::foodInsideSnakeOffset,
                             GameParameters::foodInsideSnakeSize,
                             GameParameters::foodInsideSnakeSize);
    }
}

Direction SnakeSegment::move(Direction direction)
{
    switch(direction)
    {
        case Direction::left:
            coordinates_ += {-1, 0};
            break;

        case Direction::right:
            coordinates_ += {+1, 0};
            break;

        case Direction::up:
            coordinates_ += {0, -1};
            break;

        case Direction::down:
            coordinates_ += {0, +1};
            break;
    }

    return direction;
}

HeadSegment::HeadSegment(const Coordinates& coordinates, Direction& direction) : SnakeSegment(coordinates), direction_(direction)
{

}

QRectF HeadSegment::boundingRect() const
{
    return SnakeSegment::boundingRect();
}

void HeadSegment::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    const int offsetX_ = 0;
    const int offsetY_ = 0;

    painter->setBrush(GameParameters::snakeHeadColor);
    painter->setPen(Qt::NoPen);
    painter->drawRect(coordinates_.x_ * GameParameters::snakeSegmentSize + offsetX_,
                      coordinates_.y_ * GameParameters::snakeSegmentSize + offsetY_,
                      GameParameters::snakeSegmentSize,
                      GameParameters::snakeSegmentSize);

    if(isFoodInside_)
    {
        painter->setBrush(GameParameters::foodInsideSnakeColor);
        painter->drawEllipse(coordinates_.x_ * GameParameters::snakeSegmentSize + offsetX_ + GameParameters::foodInsideSnakeOffset,
                             coordinates_.y_ * GameParameters::snakeSegmentSize + offsetY_ + GameParameters::foodInsideSnakeOffset,
                             GameParameters::foodInsideSnakeSize,
                             GameParameters::foodInsideSnakeSize);
    }

    auto drawEyes = [this, &painter](int eye1XOffset, int eye1YOffset, int eye2XOffset, int eye2YOffset)
    {
        painter->setBrush(GameParameters::snakeEyesColor);
        painter->setPen(Qt::NoPen);

        painter->drawEllipse(coordinates_.x_ * GameParameters::snakeSegmentSize + eye1XOffset,
                             coordinates_.y_ * GameParameters::snakeSegmentSize + eye1YOffset,
                             GameParameters::snakeEyeSize,
                             GameParameters::snakeEyeSize);

        painter->drawEllipse(coordinates_.x_ * GameParameters::snakeSegmentSize + eye2XOffset,
                             coordinates_.y_ * GameParameters::snakeSegmentSize + eye2YOffset,
                             GameParameters::snakeEyeSize,
                             GameParameters::snakeEyeSize);
    };

    switch(direction_)
    {
        case Direction::left:
            drawEyes(5, 5, 5, 20);
            break;

        case Direction::right:
            drawEyes(20, 5, 20, 20);
            break;

        case Direction::up:
            drawEyes(5, 5, 20, 5);
            break;

        case Direction::down:
            drawEyes(5, 20, 20, 20);
            break;
    }
}
