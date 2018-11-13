#include "food.h"
#include "config_prod.h"
#include <QPainter>

Food::Food(const Coordinates& coordinates) : CustomGraphicsItem(coordinates.x_, coordinates.y_), coordinates_(coordinates)
{
    //qDebug() << "Creating food";
}

Food::~Food()
{
    //qDebug() << "Destroying food";
}

void Food::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    CustomGraphicsItem::paint(painter, option, widget);

    painter->setPen(Qt::NoPen);
    painter->setBrush(COLOR);
    painter->drawEllipse(rect_);
}

void Food::moveToNewCoordinates(const Coordinates& coordinates)
{
    coordinates_ = coordinates;
    rect_.setRect(coordinates_.x_ * ConfigProd::Arena::PRIMARY_SQUARE_SIZE, coordinates_.y_ * ConfigProd::Arena::PRIMARY_SQUARE_SIZE, ConfigProd::Arena::PRIMARY_SQUARE_SIZE, ConfigProd::Arena::PRIMARY_SQUARE_SIZE);
}
