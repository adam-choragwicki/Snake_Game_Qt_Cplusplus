#include "wall.h"
#include "config_prod.h"
#include <QPainter>

Wall::Wall(int x, int y) : CustomGraphicsItem(x, y)
{

}

void Wall::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    CustomGraphicsItem::paint(painter, option, widget);

    painter->setPen(Qt::NoPen);
    painter->setBrush(COLOR);
    painter->drawRect(rect_);
}
