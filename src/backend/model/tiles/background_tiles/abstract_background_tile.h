#pragma once

#include "model/custom_graphics_item.h"
#include <QColor>

class AbstractBackgroundTile : public CustomGraphicsItem
{
public:
    AbstractBackgroundTile(int x, int y, const QColor& color);

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    QColor color_;
};
