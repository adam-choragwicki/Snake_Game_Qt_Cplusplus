#include "abstract_background_tile.h"
#include <QPainter>

AbstractBackgroundTile::AbstractBackgroundTile(int x, int y, const QColor& color) : CustomGraphicsItem(x, y), color_(color)
{}

void AbstractBackgroundTile::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    CustomGraphicsItem::paint(painter, option, widget);

    painter->setPen(Qt::NoPen);
    painter->setBrush(color_);
    painter->drawRect(rect_);
}
