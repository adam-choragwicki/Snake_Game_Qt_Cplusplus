#include "custom_graphics_item.h"
#include "id_generator.h"
#include "config_prod.h"
#include "coordinates.h"
#include <QPainter>

CustomGraphicsItem::CustomGraphicsItem(const QRectF& rect) : rect_(rect), id_(IdGenerator::generateId())
{
    pen_ = Qt::NoPen;
    rectPen_ = QPen(Qt::red, 1);
}

CustomGraphicsItem::CustomGraphicsItem(int x, int y) :
        rect_(QRectF(x * ConfigProd::Arena::PRIMARY_SQUARE_SIZE, y * ConfigProd::Arena::PRIMARY_SQUARE_SIZE, ConfigProd::Arena::PRIMARY_SQUARE_SIZE, ConfigProd::Arena::PRIMARY_SQUARE_SIZE)), id_(IdGenerator::generateId())
{

}

QRectF CustomGraphicsItem::boundingRect() const
{
    return rect_;
}

void CustomGraphicsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    if(drawRect_)
    {
        painter->setPen(rectPen_);
        painter->drawRect(rect_);
    }
}

void CustomGraphicsItem::setPositionOnSceneAtCoordinates(Coordinates& coordinates)
{
    setPos(coordinates.x_ * ConfigProd::Arena::PRIMARY_SQUARE_SIZE, coordinates.y_ * ConfigProd::Arena::PRIMARY_SQUARE_SIZE);
}
